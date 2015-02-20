#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <llvm/Support/raw_ostream.h>

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;

static llvm::cl::OptionCategory toolingCategory("tooling-test");


class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
  public:
    MyASTVisitor(Rewriter & r)
      : rewriter(r)
    {}
  private:
    Rewriter & rewriter;
};



class MyASTConsumer : public ASTConsumer
{
  public:
    MyASTConsumer(Rewriter & r)
      : visitor(r)
    {}
    bool HandleTopLevelDecl(DeclGroupRef dr) override
    {
      for (DeclGroupRef::iterator b = dr.begin(), e =dr.end(); b != e; ++b)
      {
        visitor.TraverseDecl(*b);
        (*b)->dump();
      }
      return true;
    }
  private:
    MyASTVisitor visitor;
};


class MyFrontendAction : public ASTFrontendAction
{
  public:
    MyFrontendAction()
    {}
    void EndSourceFileAction() override
    {
      SourceManager & sm = rewriter.getSourceMgr();
      llvm::errs() << "** EndSourceFileAction for: "
        << sm.getFileEntryForID(sm.getMainFileID())->getName() << "\n";
      rewriter.getEditBuffer(sm.getMainFileID()).write(llvm::outs());
    }
    std::unique_ptr<ASTConsumer> CreateAstConsumer(
        CompilerInstance & ci,
        StringRef file) override
    {
      llvm::errs() << "** Creating AST consumer for: " << file << "\n";
      rewriter.setSourceMgr(ci.getSourceManager(), ci.getLangOpts());
      return llvm::make_unique<MyASTConsumer>(rewriter);
    }
  private:
    Rewriter rewriter;
};

int main(int argc, char const ** argv)
{
  CommonOptionsParser op(argc, argv, toolingCategory);
  ClangTool tool(op.getCompilations(), op.getSourcePathList());
  return tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}

