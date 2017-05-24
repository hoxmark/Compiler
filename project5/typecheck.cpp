#include "typecheck.hpp"

// Defines the function used to throw type errors. The possible
// type errors are defined as an enumeration in the header file.
void typeError(TypeErrorCode code) {
  switch (code) {
    case undefined_variable:
      std::cerr << "Undefined variable." << std::endl;
      break;
    case undefined_method:
      std::cerr << "Method does not exist." << std::endl;
      break;
    case undefined_class:
      std::cerr << "Class does not exist." << std::endl;
      break;
    case undefined_member:
      std::cerr << "Class member does not exist." << std::endl;
      break;
    case not_object:
      std::cerr << "Variable is not an object." << std::endl;
      break;
    case expression_type_mismatch:
      std::cerr << "Expression types do not match." << std::endl;
      break;
    case argument_number_mismatch:
      std::cerr << "Method called with incorrect number of arguments." << std::endl;
      break;
    case argument_type_mismatch:
      std::cerr << "Method called with argument of incorrect type." << std::endl;
      break;
    case while_predicate_type_mismatch:
      std::cerr << "Predicate of while loop is not boolean." << std::endl;
      break;
    case repeat_predicate_type_mismatch:
      std::cerr << "Predicate of repeat loop is not boolean." << std::endl;
      break;
    case if_predicate_type_mismatch:
      std::cerr << "Predicate of if statement is not boolean." << std::endl;
      break;
    case assignment_type_mismatch:
      std::cerr << "Left and right hand sides of assignment types mismatch." << std::endl;
      break;
    case return_type_mismatch:
      std::cerr << "Return statement type does not match declared return type." << std::endl;
      break;
    case constructor_returns_type:
      std::cerr << "Class constructor returns a value." << std::endl;
      break;
    case no_main_class: //DONE
      std::cerr << "The \"Main\" class was not found." << std::endl;
      break;
    case main_class_members_present:
      std::cerr << "The \"Main\" class has members." << std::endl;
      break;
    case no_main_method:
      std::cerr << "The \"Main\" class does not have a \"main\" method." << std::endl;
      break;
    case main_method_incorrect_signature:
      std::cerr << "The \"main\" method of the \"Main\" class has an incorrect signature." << std::endl;
      break;
  }
  exit(1);
}

// TypeCheck Visitor Functions: These are the functions you will
// complete to build the symbol table and type check the program.
// Not all functions must have code, many may be left empty.

void TypeCheck::visitProgramNode(ProgramNode* node) {
  // Det er her det starter. 
  // std::cout << node << "\n";
  // // std::cout << "visitProgramNode" << "\n";
  classTable = new ClassTable(); //std::map<std::string, ClassInfo> ClassTable
  
  // classTable->insert(std::pair<std::string, ClassInfo>(currentClassName, thisClassInfo));
  
  node->visit_children(this);

  //Type: No Main Class - no_main_class 
  if ((*classTable).count("Main")==1){
    // std::cout << "#OK"<<"\n";
  } else {
    // std::cout<< "#NOTOK"<<"\n";
    typeError(no_main_class);
  }

    // ClassInfo *classInfo = &(*classTable)["Main"];
    // // Methodinfo *methodInfo = &(*classInfo)[];
    
    // std::cout<< "name of classes" <<  &classInfo  <<"\n";


}

void TypeCheck::visitClassNode(ClassNode* node) {
  // // std::cout << "visitClassNode" << "\n";
  currentClassName = node->identifier_1->name;
  std::string currentSuperClassName;

  // Setting superclassname 
  if (node->identifier_2){
    currentSuperClassName = node->identifier_2->name;
    
    //TYPE:  undefined_class
    if ((*classTable).count(currentSuperClassName)!=1){
      typeError(undefined_class);
    }


  } else {
    currentSuperClassName = "";    
  }


  


  ClassInfo thisClassInfo;
  thisClassInfo.superClassName = currentSuperClassName;

  currentMethodTable = new MethodTable();
  thisClassInfo.methods = currentMethodTable;
  
  this->currentVariableTable = new VariableTable();
  thisClassInfo.members = currentVariableTable;
  // // std::cout<< "Member: " << thisClassInfo.members << "\n";
  // // std::cout<< "Member2: " << currentVariableTable << "\n";

  (*classTable)[currentClassName] = thisClassInfo;
  currentLocalOffset = 0;
 
  // // std::cout<< "Member3: " <<  &(*classTable)[currentClassName].members  << "\n";
  node->visit_children(this);
  // classTable->insert(std::pair<std::string, ClassInfo>(currentClassName, thisClassInfo));
  
  // WRITEME: Replace with code if necessary
  //set current method table. 
  //set current ... tale aswell ( need to always update this all the time . )

  //Make a classTable id1, id2(superclass), methoods(allocate memory for this), members=----
  //method= new Methods table. 
  // Når man er i method node så vil man kunne bruke noe som heter currentClassNode(). <- i denne er det en 
  /*
    #b Les offsets slide # 
    starter på ocal var 12. 

    currentLocalOffset 
    currentPatameterOffset
    currentMemberOffset
    this need to be updated all the time. 
  */
  //TODO, telle her? 
  
}

// bool TypeCheck::isMethodInSuperClass(ClassNode* node){
//   std::string currentSuperClassName;
//   // Setting superclassname  
//   if (node->identifier_2){
//     // currentSuperClassName = node->identifier_2->name;
//     // //Sjekk
//     // ClassInfo sClassinfo = (*classTable)[currentSuperClassName]; 
//     // if (sClassinfo->methods->count(methodName)==1){
//     //   return true; 
//     // }

//     // //neste 
//     // return isMethodInSuperClass((*classTable)[currentSuperClassName], methodName);
  
//     return false; 

//   } else {
//     return false ;
//   }
// }

void TypeCheck::visitMethodNode(MethodNode* node) {
  // // std::cout << "visitMethodNode" << "\n";
  std::string currentMethodName = node -> identifier -> name;

  currentParameterOffset = 12;
  currentLocalOffset = -4;

  MethodInfo thisMethodInfo; 
  currentVariableTable = new VariableTable();
  thisMethodInfo.variables = currentVariableTable;
  
  node->visit_children(this);
  
  CompoundType compoundType;
  compoundType.baseType = node->type->basetype;
  compoundType.objectClassName = node->type->objectClassName;
  
  thisMethodInfo.returnType = compoundType;
  
  thisMethodInfo.localsSize = -(currentLocalOffset+4);
  (*currentMethodTable)[currentMethodName] = thisMethodInfo;
  



    

    
    

}


void TypeCheck::visitMethodBodyNode(MethodBodyNode* node) {
  // // std::cout << "visitMethodBodyNode" << "\n";
  
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary 
}

void TypeCheck::visitParameterNode(ParameterNode* node) {
  // // std::cout << "visitParameterNode type:"  << " id: " << node->identifier->name<< "\n";
  std::string currentVarName = node -> identifier -> name;
  
  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->type->basetype;
  compoundType.objectClassName = node->type->objectClassName;

  VariableInfo variableInfo;
  variableInfo.type = compoundType; 
  variableInfo.offset = currentParameterOffset;
  variableInfo.size = 4 ; 
  currentParameterOffset += 4;

  (*currentVariableTable)[currentVarName] = variableInfo;
    
}

void TypeCheck::visitDeclarationNode(DeclarationNode* node) {
  // // std::cout << "visitDeclarationNode type:" <<  "\n";
 
  if ((*classTable)[currentClassName].members == this->currentVariableTable){
    node->visit_children(this);

    CompoundType compoundType;
    compoundType.baseType = node->type->basetype;
    compoundType.objectClassName = node->type->objectClassName;
      
    for(std::list<IdentifierNode*>::iterator idNode = node->identifier_list->begin();
          idNode != node->identifier_list->end(); idNode++) {
        
        std::string currentVarName = (*idNode) -> name;
        int size = currentVariableTable->size();
        VariableInfo variableInfo;
        variableInfo.type = compoundType; 
        variableInfo.offset = currentLocalOffset;
        variableInfo.size = 4 ; 
        currentLocalOffset += 4;
        (*currentVariableTable)[currentVarName] = variableInfo;
        
      }       

  } else {
    node->visit_children(this);

    CompoundType compoundType;
    compoundType.baseType = node->type->basetype;
    compoundType.objectClassName = node->type->objectClassName;
      
    for(std::list<IdentifierNode*>::iterator idNode = node->identifier_list->begin();
          idNode != node->identifier_list->end(); idNode++) {
        
        std::string currentVarName = (*idNode) -> name;
        int size = currentVariableTable->size();
        VariableInfo variableInfo;
        variableInfo.type = compoundType; 
        variableInfo.offset = currentLocalOffset;
        variableInfo.size = 4 ; 
        currentLocalOffset -= 4;
        (*currentVariableTable)[currentVarName] = variableInfo;
      
      }       
  }    
}

void TypeCheck::visitReturnStatementNode(ReturnStatementNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitAssignmentNode(AssignmentNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitCallNode(CallNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitIfElseNode(IfElseNode* node) {
  // WRITEME: Replace with code if necessary
  
  //if_predicate_type_mismatch  
  node->visit_children(this);
  
  std::cout << "her:" <<node->expression->basetype<<"\n";
}

void TypeCheck::visitWhileNode(WhileNode* node) {
  // WRITEME: Replace with code if necessary
  //while_predicate_type_mismatch
  node->visit_children(this);
  


}

void TypeCheck::visitRepeatNode(RepeatNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
  
}

void TypeCheck::visitPrintNode(PrintNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitPlusNode(PlusNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
  
  // std::cout <<"plus1"<< node->expression_1->basetype << "\n";
  // std::cout <<"plus2"<< node->expression_2->basetype << "\n";
}

void TypeCheck::visitMinusNode(MinusNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitTimesNode(TimesNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
  
}

void TypeCheck::visitDivideNode(DivideNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitLessNode(LessNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);

  // CompoundType compoundType;
  // compoundType.baseType = node->expression_1->basetype;

  // std::cout <<"lessNode1 "<< string(compoundType) << "\n";
  // std::cout <<"lessNode2 "<< node->expression_2->basetype << "\n";
}

void TypeCheck::visitLessEqualNode(LessEqualNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitEqualNode(EqualNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitAndNode(AndNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitOrNode(OrNode* node) {
  // WRITEME: Replace with code if necessary
  node->visit_children(this);

  // CompoundType compoundType;
  // compoundType.baseType = node->expression_1->basetype;

  // std::cout <<"OR1 "<< node->expression_1->basetype << "\n";
  // std::cout <<"OR2 "<< node->expression_2->basetype << "\n";

  // if (node->expression_1->basetype != 1 || node->expression_2->basetype != 1){
  //   typeError(expression_type_mismatch);
  // } 

}

void TypeCheck::visitNotNode(NotNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNegationNode(NegationNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitMethodCallNode(MethodCallNode* node) {
  std::cout<< "visitMethodCallNode" << "\n";
  node->visit_children(this);

  std::string identifier_1 = node -> identifier_1 -> name;
  

  /*  
    Undefined Method - undefined_method 
    This applies when a method is called on an object (or on the current object) 
    that does not exist in the class of that object or any super class.
    */
    //TYPE undefined_method in this class. 
    ClassInfo classinfo = (*classTable)[currentClassName];
    bool inCurrentClassinfo;
    if (classinfo.methods->count(identifier_1)==0){
      inCurrentClassinfo = false;
    } else {
      inCurrentClassinfo = true;
    }
    

    bool inValidClassinfo;
    if(node -> identifier_2){
      std::string identifier_2 = node -> identifier_2 -> name;
      VariableInfo variableInfo = (*currentVariableTable)[identifier_2];
      std::cout << "variableInfo Info: " + string(variableInfo.type) + "\n";
      // ClassInfo classinfo = (*classTable)[identifier_1];    
      // if (classinfo->methods->count(identifier_2)==0){
      //   inCurrentClassinfo = false;
      // } else {
      //   inCurrentClassinfo = true;
      // }
    }




    std::cout<< "REC START"<<"\n";
    // bool inSuperClass = isMethodInSuperClass( &(*classTable)[currentClassName]);
    std::cout<< "REC STOP"<<"\n";


   //TYPE:  undefined_class TODO CONSTRUCTOR
    // if ((*classTable).count(nodeId)!=1){
    //   typeError(undefined_class);
    // }
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitMemberAccessNode(MemberAccessNode* node) {
  node->visit_children(this);
  
  // // std::cout<<"visitMemberAccessNode"<<"\n";
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitVariableNode(VariableNode* node) {
  std::string nodeId = node->identifier->name;
  ClassInfo *classInfo =  &(*classTable)[currentClassName];
  std::string superClassname = (*classInfo).superClassName;

  // std::cout << "id: \t"<< nodeId << "\n";
  // std::cout << "super: \t"<< superClassname << "\n";
  // std::cout << "currentVariableTable\t"<< (*currentVariableTable).count(nodeId) << "\n";
  // std::cout << "classInfo.members\t"<< (*classInfo).members->count(nodeId) << "\n";
  if (superClassname != ""){
    ClassInfo *superClassInfo = &(*classTable)[superClassname];
    if (((*currentVariableTable).count(nodeId) == 0) && ((*classInfo).members->count(nodeId) == 0) && ((*superClassInfo).members->count(nodeId)==0 )){
      typeError(undefined_variable);
    }

  } else {
    if (((*currentVariableTable).count(nodeId) == 0) && ((*classInfo).members->count(nodeId) == 0) ){
      typeError(undefined_variable);
    }
  }

}


void TypeCheck::visitIntegerLiteralNode(IntegerLiteralNode* node) {
  node->basetype = bt_integer;    
  std::cout<<"visitIntegerLiteralNode"<<"\n";
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitBooleanLiteralNode(BooleanLiteralNode* node) {
  node->basetype = bt_boolean;  
  std::cout<<"visitBooleanLiteralNode"<<node->integer->value<<"\n";
  std::cout<<node->integer->value<<"\n";
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNewNode(NewNode* node) {
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIntegerTypeNode(IntegerTypeNode* node) {
  node->basetype = bt_integer;

  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitBooleanTypeNode(BooleanTypeNode* node) {
  // WRITEME: Replace with code if necessary
  node->basetype = bt_boolean;
  
}

void TypeCheck::visitObjectTypeNode(ObjectTypeNode* node) {
  // WRITEME: Replace with code if necessary
  node->basetype = bt_object;
  node->objectClassName = node->identifier->name;
  // // std::cout << "ppp "<< node->identifier->name <<"\n";

  
}

void TypeCheck::visitNoneNode(NoneNode* node) {
  // std::cout<<"NONE --"<< node->basetype << "\n";
  node->basetype = bt_none;

  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIdentifierNode(IdentifierNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIntegerNode(IntegerNode* node) {
  // WRITEME: Replace with code if necessary
}


// The following functions are used to print the Symbol Table.
// They do not need to be modified at all.

std::string genIndent(int indent) {
  std::string string = std::string("");
  for (int i = 0; i < indent; i++)
    string += std::string(" ");
  return string;
}


std::string string(CompoundType type) {
  switch (type.baseType) {
    case bt_integer:
      return std::string("Integer");
    case bt_boolean:
      return std::string("Boolean");
    case bt_none:
      return std::string("None");
    case bt_object:
      return std::string("Object(") + type.objectClassName + std::string(")");
    default:
      return std::string("");
  }
}

void print(VariableTable variableTable, int indent) {
  std::cout << genIndent(indent) << "VariableTable {";
  if (variableTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (VariableTable::iterator it = variableTable.begin(); it != variableTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << string(it->second.type);
    std::cout << ", " << it->second.offset << ", " << it->second.size << "}";
    if (it != --variableTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(MethodTable methodTable, int indent) {
  std::cout << genIndent(indent) << "MethodTable {";
  if (methodTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (MethodTable::iterator it = methodTable.begin(); it != methodTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    std::cout << genIndent(indent + 4) << string(it->second.returnType) << "," << std::endl;
    std::cout << genIndent(indent + 4) << it->second.localsSize << "," << std::endl;
    print(*it->second.variables, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --methodTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(ClassTable classTable, int indent) {
  std::cout << genIndent(indent) << "ClassTable {" << std::endl;
  for (ClassTable::iterator it = classTable.begin(); it != classTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    if (it->second.superClassName != "")
      std::cout << genIndent(indent + 4) << it->second.superClassName << "," << std::endl;
    print(*it->second.members, indent + 4);
    std::cout << "," << std::endl;
    print(*it->second.methods, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --classTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}" << std::endl;
}

void print(ClassTable classTable) {
  print(classTable, 0);
}

  // int counter = 0; 
  // std::map<std::string, VariableInfo>::iterator iter;
  // for(iter = currentVariableTable->begin();
  //       iter != currentVariableTable->end(); iter++) {
          
          // // std::cout<< "her"<< iter->second.offset <<" \n";
  //         if (iter->second.offset>=12) {
  //           counter++;
  //         }

  //   }    