#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"


using namespace clang::tooling;

int main(int argc, char const ** argv)
{
  CommonOptionsParser op(argc, argv);
  ClangTool tool(op.getCompilations(), op.getSourcePathList());
  return tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>());
}

