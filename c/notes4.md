# C Notes (part 4)

## Function Pointers
  * All functions of C are declared in the top-most scope; there are no lambdas.
  * You pass a function pointer by just passing its name.
  * `map(root, functionName);`
  * You don't need to dereference function pointers.
  * Type of functions are:
    * `returnType (*)(FunctionSignature) fn = printTreeNode;`
    * This is quite annoying, so commonly we will typedef function pointer types.
    * `typedef (void (*)(IntTreeNode*)) IntTreeNodeCallback`
    * Then you can replace it with: `IntTreeNodeCallback fn = printTreeNode`;
