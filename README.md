# ccsds-tool

Given a C++ class definition, produce code to correctly serialize the class.
Additional library code helps packing the serialized data into ccsds protocol packages / frames.

Other software / projects to consider:
* http://en.wikipedia.org/wiki/Comparison_of_data_serialization_formats
* Google Protocol Buffers
* http://yuasatakayuki.github.io/CCSDSLibrary/
* Boost::serialize

Potential resources:
* http://4thmouse.com/index.php/2009/11/15/overview-of-the-ccsds-network-protocols/

## Some notes, points to discuss
* Using the C++ class declaration means there is no need to learn a "serialization language", as is with protobuf. Though this may not be *that* important.
* Generating code "outside" of the (target) language - metaprogramming - makes debugging the generated code quite difficult. Though depending on the complexity of the generated code, this may not be an issue.
* Using a language like Haskell / Lisp as meta language makes formal reasoning about the code generation possible, potentionally reducing the risk of bugs in de/serialization code.
* Using a language like Haskell / Lisp on top of C++ makes it possible to combine benefits of each of the languages.
* Parsing C++ is hard. Using clang to parse class declarations helps keeping up with future additions / changes of the C++ language.
* As both code size and speed are important, there must not be any dependencies of the genereated code or the library code.
* Less is more, library design should be focused on the use cases (todo). This removes flexibility, but also improves ease-of-use as well as code size / performance.
* Using a library (C++) for serialization requires the programmer to adjust his code, thus cluttering the code with "housekeeping" jobs. Using external code generation seperates these aspects, similar to aspect oriented programming.
* Using the C++ class declaration somewhat limits both end points to that language. Using a "serialization language" makes it possible to specify data exchange independent of used language.
* Possible future additions, RPC calls, for satelite networks
