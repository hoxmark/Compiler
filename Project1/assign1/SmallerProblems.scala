// These problems are extracted from "Programming Scala", by
// Dean Wampler.

object Problem1 {
    def main( args:Array[String] ) = {
      println("problem 1")

      
      val list: List[String] = args.toList.map(_.reverse)
      for (elem <- list) {println(elem)}    
      
      // Reverse each element of the args array and print out the
      // result, with each element printed on a new line.
      // Note that the String class has a 'reverse' method.
      //
      // For example:
      //
      // scala Problem1 foo bar baz
      // oof
      // rab
      // zab
    }
}

object Problem2 {
  // A binary tree node.  The field `ord` is declared with
  // `var`, so it is mutable.  For example, you can do:
  //
  // val n = Node(...)
  // n.ord = (1 -> 2)
  //
  // Because we introduced the `var`, you may modify _this_ `var`.
  // You may not introduce any other `var`s.
  case class Node(var ord:(Int,Int), 
                  left:Option[Node],
                  right:Option[Node])

  def main( args:Array[String] ) = {
    // example tree
    val tree =              Node( (-1,-1), 
                              None,
                      Some(Node( (-1,-1),
                Some(Node( (-1,-1), None, None )),
                Some(Node( (-1,-1), Some(Node( (-1,-1), None, None )), None ))
      ))
    )
    
    // set the tree nodes' labels and print the tree. note that case
    // classes are automatically given a toString method, so we don't
    // need to define our own.  Your solution must be general, in that
    // it can work with arbitrary trees.
    print(tree)
    order( tree )
    println( tree )

    // For example:
    //
    // scala Problem2
    // Node((0,4),None,Some(Node((1,3),Some(Node((2,0),None,None)),Some(Node((3,2),Some(Node((4,1),None,None)),None)))))
    // Node((0,0),None,Some(Node((1,0),Some(Node((2,0),None,None)),Some(Node((3,0),Some(Node((4,0),None,None)),None)))))
  }


  def order( node:Node ) {
    //Was only able to implement preOrder, not postOrder
    def preOrder(node: Node, counter:Int){
      node.ord = node.ord.copy(_1 = counter)

      if ((node.left==None) && (node.right == None)){
        return
      } else {
        val leftVal = counter + 1 
        val leftOK = if (node.left isDefined) {
          preOrder(node.left.get, leftVal) 
          true
          } else false
        val rightValue = if (leftOK) (counter + 2) else (counter +1)
        if (node.right isDefined) preOrder(node.right.get, rightValue)  else false
      }
      println(node.ord)            
    }  
      
    //def postOrder(node: Node, counter:Int):Int = {
        //Not implemented. 
    //}  
      

    preOrder(node,0)
    // use a nested method inside this method as a helper function to
    // traverse the given tree and set each Node's 'ord' field to the
    // tuple '(preorder, postorder)', where 'preorder' is the Node's
    // preorder label and 'postorder' is the Node's postorder
    // label. For consistent numbers, visit left children before right
    // children. Labels should start at 0 (i.e., the root node's
    // preorder label should be 0).

    // As a hint, you'll need to use recursion here.  The nested
    // method should have an auxilliary parameter, representing the
    // currently available ID.  The nested method should return the
    // next available ID.  This is equivalent to an approach of
    // having a mutable variable elsewhere and incrementing it
    // each time we need a new ID, which is likely a more obvious
    // solution if you're coming from an imperative background.  This
    // is equivalent, because the mutable variable sets up an implicit
    // data dependency between recursive calls, whereas with functional
    // purity we must make this data dependency explicit.
  }
}

object Problem3 {
  def main( args:Array[String] ) = {
    // Use the foldLeft method of list to print the following:
    //
    // 1. the largest element in args (using string comparison)
    // 2. args with no duplicate elements
    // 3. a run-length-encoded version of args

    // NOTES
    //
    // If the initial value given to foldLeft is an empty List you
    // need to explicitly give the type of the List, e.g., List[Int]()
    // or List[String](), otherwise the compiler won't be able to
    // figure out the types.
    //
    // To determine if a string `s1` is greater than another string `s2`,
    // you can use `>` like so: `s1 > s2`.  The `compareTo` method on
    // `String` can also be used.
    // 
    // You may use reverse as part of your solution.
    //
    // For run-length-encoding specifics, see
    // http://en.wikipedia.org/wiki/Run_length_encoding.

    // For example:
    //
    // scala Problem3 foo bar bar baz moo moo moo cow
    // moo
    // List(foo, bar, baz, moo, cow)
    // List((foo,1), (bar,2), (baz,1), (moo,3), (cow,1))

    val list = args.toList
    println(list)

    val assignment1 = list.foldLeft("")((x,y) => if (x>y) x else y)
    println(assignment1)
    
    //x is baseline List 
    val assignment2 = list.foldLeft(List[String]())((x:List[String],y) => if (x.contains(y)) x else y::x )
    println(assignment2)

    //x is baseline Map() 
    val assignment3 = list.foldLeft(Map[String, Int]())((x,y) => if (x.contains(y)) (x + (y->(x(y)+1))) else (x + (y->1)) )
    println(assignment3.toList) 
  }
}




    //match  ?? kanskje? 
//    random.nextInt(3) match {
//  case 0 => println("Saw 0")
//  case 1 => println("Saw 1")
//  case 2 => println("Saw 2")
//  case _ => println("Don't know what I saw")
//}

  //   if (node.left != None) {
  //       node.left.order
  //     } else if (node.right != None) {
  //       node.right.order
  //     } else {
  //       println("Default")
  //     }

  

  // println(node.left)
  // println(node.right)
  // node match{
  //   case node.left => println("None left")
  //   case node.right => println("None Right")
  //   case _ => println("Default")
  // }

  
// if (node.left == None) {node.right.order} else if (node.right ==None) node.left.order

