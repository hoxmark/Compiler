#include "typecheck.hpp"

// Defines the function used to throw type errors. The possible
// type errors are defined as an enumeration in the header file.
void typeError(TypeErrorCode code)
{
  switch (code)
  {
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

void TypeCheck::visitProgramNode(ProgramNode *node)
{
  // std::cout << node << "\n";
  classTable = new ClassTable(); //std::map<std::string, ClassInfo> ClassTable

  // classTable->insert(std::pair<std::string, ClassInfo>(currentClassName, thisClassInfo));

  node->visit_children(this);

  //Type: No Main Class - no_main_class
  if ((*classTable).count("Main") == 1)
  {
    // std::cout << "#OK"<<"\n";
  }
  else
  {
    // std::cout<< "#NOTOK"<<"\n";
    typeError(no_main_class);
  }
}

void TypeCheck::visitClassNode(ClassNode *node)
{
  // // std::cout << "visitClassNode" << "\n";
  currentClassName = node->identifier_1->name;
  std::string currentSuperClassName;

  // Setting superclassname
  if (node->identifier_2)
  {
    currentSuperClassName = node->identifier_2->name;

    //TYPE:  undefined_class
    if ((*classTable).count(currentSuperClassName) != 1)
    {
      typeError(undefined_class);
    }
  }
  else
  {
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

}


void TypeCheck::visitMethodNode(MethodNode *node)
{
  // // std::cout << "visitMethodNode" << "\n";
  std::string currentMethodName = node->identifier->name;

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

  thisMethodInfo.localsSize = -(currentLocalOffset + 4);
  (*currentMethodTable)[currentMethodName] = thisMethodInfo;
}

void TypeCheck::visitMethodBodyNode(MethodBodyNode *node)
{
  node->visit_children(this);
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitParameterNode(ParameterNode *node)
{
  // // std::cout << "visitParameterNode type:"  << " id: " << node->identifier->name<< "\n";
  std::string currentVarName = node->identifier->name;

  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->type->basetype;
  compoundType.objectClassName = node->type->objectClassName;

  VariableInfo variableInfo;
  variableInfo.type = compoundType;
  variableInfo.offset = currentParameterOffset;
  variableInfo.size = 4;
  currentParameterOffset += 4;

  (*currentVariableTable)[currentVarName] = variableInfo;
}

void TypeCheck::visitDeclarationNode(DeclarationNode *node)
{
  // // std::cout << "visitDeclarationNode type:" <<  "\n";

  if ((*classTable)[currentClassName].members == this->currentVariableTable)
  {
    node->visit_children(this);

    CompoundType compoundType;
    compoundType.baseType = node->type->basetype;
    compoundType.objectClassName = node->type->objectClassName;

    for (std::list<IdentifierNode *>::iterator idNode = node->identifier_list->begin();
         idNode != node->identifier_list->end(); idNode++)
    {

      std::string currentVarName = (*idNode)->name;
      int size = currentVariableTable->size();
      VariableInfo variableInfo;
      variableInfo.type = compoundType;
      variableInfo.offset = currentLocalOffset;
      variableInfo.size = 4;
      currentLocalOffset += 4;
      (*currentVariableTable)[currentVarName] = variableInfo;
    }
  }
  else
  {
    node->visit_children(this);

    CompoundType compoundType;
    compoundType.baseType = node->type->basetype;
    compoundType.objectClassName = node->type->objectClassName;

    for (std::list<IdentifierNode *>::iterator idNode = node->identifier_list->begin();
         idNode != node->identifier_list->end(); idNode++)
    {

      std::string currentVarName = (*idNode)->name;
      int size = currentVariableTable->size();
      VariableInfo variableInfo;
      variableInfo.type = compoundType;
      variableInfo.offset = currentLocalOffset;
      variableInfo.size = 4;
      currentLocalOffset -= 4;
      (*currentVariableTable)[currentVarName] = variableInfo;
    }
  }
}

void TypeCheck::visitReturnStatementNode(ReturnStatementNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitAssignmentNode(AssignmentNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitCallNode(CallNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void TypeCheck::visitIfElseNode(IfElseNode *node)
{
  // WRITEME: Replace with code if necessary

  //if_predicate_type_mismatch
  node->visit_children(this);

  // std::cout << "node: " << node->expression << "\n";
  // std::cout << "her: " << node->expression->basetype << "\n";

  if (node->expression->basetype != 1)
  {
    typeError(if_predicate_type_mismatch);
  }

  
}

void TypeCheck::visitWhileNode(WhileNode *node)
{
  // WRITEME: Replace with code if necessary
  //while_predicate_type_mismatch
  node->visit_children(this);
  if (node->expression->basetype != 1)
  {
    typeError(while_predicate_type_mismatch);
  }
}

void TypeCheck::visitRepeatNode(RepeatNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
   if (node->expression->basetype != 1){
      typeError(repeat_predicate_type_mismatch);

   }
}

void TypeCheck::visitPrintNode(PrintNode *node)
{
  node->visit_children(this);

  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitPlusNode(PlusNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);

  // std::cout <<"plus1"<< node->expression_1->basetype << "\n";
  // std::cout <<"plus2"<< node->expression_2->basetype << "\n";
   // Inly fr Int
  if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0) {
        typeError(expression_type_mismatch);
    }
}

void TypeCheck::visitMinusNode(MinusNode *node)
{
  node->visit_children(this);
  // Inly fr Int
  if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0) {
        typeError(expression_type_mismatch);
    }
}

void TypeCheck::visitTimesNode(TimesNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);
  // Only for Int
    if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0) {
        typeError(expression_type_mismatch);
    }
}

void TypeCheck::visitDivideNode(DivideNode *node)
{
    node->visit_children(this);
    
    // Only for Int
    if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0) {
        typeError(expression_type_mismatch);
    }
}

void TypeCheck::visitLessNode(LessNode *node)
{
  node->visit_children(this);

 
  // std::cout << "LESSTHAN1 " << node->expression_1->basetype << "\n";
  // std::cout << "LESSTHAN2 " << node->expression_2->basetype << "\n";

  // if () only INT
  if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0)
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }
}

void TypeCheck::visitLessEqualNode(LessEqualNode *node)
{
  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->expression_1->basetype;

  // std::cout << "LESSEQUALTHAN1 " << node->expression_1->basetype << "\n";
  // std::cout << "LESSEQUALTHAN2 " << node->expression_2->basetype << "\n";

  // if ()
  if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0)
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }

  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitEqualNode(EqualNode *node)
{
  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->expression_1->basetype;

  // std::cout << "EQUAL1 " << node->expression_1->basetype << "\n";
  // std::cout << "EQUAL2 " << node->expression_2->basetype << "\n";

  // if () Should  only be INT
  if (node->expression_1->basetype != 0 || node->expression_2->basetype != 0)
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitAndNode(AndNode *node)
{

  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->expression_1->basetype;

  // std::cout << "AND1 " << node->expression_1->basetype << "\n";
  // std::cout << "AND2 " << node->expression_2->basetype << "\n";
  // if ()
  if ((node->expression_1->basetype != bt_integer && node->expression_1->basetype != bt_boolean) || node->expression_1->basetype != node->expression_2->basetype )
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }
}

void TypeCheck::visitOrNode(OrNode *node)
{
  // WRITEME: Replace with code if necessary
  node->visit_children(this);

  CompoundType compoundType;
  compoundType.baseType = node->expression_1->basetype;

  // std::cout << "OR1 " << node->expression_1->basetype << "\n";
  // std::cout << "OR2 " << node->expression_2->basetype << "\n";

  // if ()
  if (node->expression_1->basetype != bt_boolean || node->expression_2->basetype != bt_boolean)
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }
}

void TypeCheck::visitNotNode(NotNode *node)
{
  node->visit_children(this);

  if (node->expression->basetype != bt_boolean)
  {
    typeError(expression_type_mismatch);
  }
  else
  {
    node->basetype = bt_boolean;
  }
}

void TypeCheck::visitNegationNode(NegationNode *node)
{
  node->visit_children(this);
  
  // WRITEME: Replace with code if necessary
  node->basetype = bt_integer; //Assinging 0, the integer value
  
  if (bt_integer != node->expression->basetype)
      typeError(expression_type_mismatch);
}

void TypeCheck::visitMethodCallNode(MethodCallNode *node)
{
  node->visit_children(this);
  bool inCurrentClassinfo = false;
  bool inObjectsClassinfo = false;
  MethodInfo localMethodInfo;
  VariableInfo classInfo;

  std::string methodId;
  std::string ObjectId;
  if (node->identifier_2)
  {
    methodId = node->identifier_2->name;
    ObjectId = node->identifier_1->name;
  }
  else
  {
    methodId = node->identifier_1->name;
    ObjectId = currentClassName;
  }

  //if it is a object.
  if (node->identifier_2)
  {
    // std::cout << " Method:  if its an object. \n";
    VariableInfo variableInfo = (*currentVariableTable)[ObjectId];
    // std::cout << "ObjectID:: " << ObjectId << "\n";
    // std::cout << "MethodID:: " << methodId << "\n";
    // std::cout << "variableInfo Info: " << string(variableInfo.type) << "\n";
    // std::cout << "classname: " + variableInfo.type.objectClassName << "\n";
    std::string tempSCName = variableInfo.type.objectClassName;
    while (tempSCName != "")
    {
      MethodTable *sClassMethods = (*classTable)[tempSCName].methods;

      inObjectsClassinfo = (sClassMethods->count(methodId) == 1);
      if (inObjectsClassinfo)
      {
        localMethodInfo = (*sClassMethods)[methodId];
        break;
      }
      else
      {
        tempSCName = (*classTable)[tempSCName].superClassName;
      }
    }

    if (variableInfo.type.objectClassName != "")
    {
      ClassInfo classinfo = (*classTable)[variableInfo.type.objectClassName];
      if (classinfo.methods->count(methodId) == 1)
      {
        inObjectsClassinfo = true;
      }
    }
    else
    {
      //TYPE not_object
      typeError(not_object);
    }

    classInfo.type.baseType = bt_object;
    classInfo.type.objectClassName = ObjectId;
  }
  else
  { // if its not an object.
    // std::cout << " Method:  if its not an object. \n";
    ClassInfo classinfo = (*classTable)[currentClassName];
    if (classinfo.methods->count(methodId) == 1)
    {
      inCurrentClassinfo = true;
    }
  }

  if (inObjectsClassinfo || inCurrentClassinfo)
  {
    // std::cout << "ONE OK \n";
  }
  else
  {
    // std::cout << "NOT OK\n";
    typeError(undefined_method);
  }
}

void TypeCheck::visitMemberAccessNode(MemberAccessNode *node)
{
  node->visit_children(this);

  // // std::cout<<"visitMemberAccessNode"<<"\n";
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitVariableNode(VariableNode *node)
{
  node->visit_children(this);

  VariableInfo variableInfo;

  bool isLegal = false;
  std::string nodeId = node->identifier->name;
  // std::string sClassname = (*classInfo).superClassName;
  bool varInVarTable = ((*currentVariableTable).count(nodeId) == 1); //Var in variableTable?

  // std::cout << "id: \t"<< nodeId << "\n";
  // std::cout << "super: \t"<< sClassname << "\n";
  // std::cout << "currentVariableTable\t"<< (*currentVariableTable).count(nodeId) << "\n";
  // std::cout << "classInfo.members\t"<< (*classInfo).members->count(nodeId) << "\n";

  if (varInVarTable)
  {
    isLegal = true;
    variableInfo = (*this->currentVariableTable)[nodeId];
  }
  else
  {
    std::string tempSCName = this->currentClassName;
    while (tempSCName != "")
    {
      VariableTable *localClassMem = (*classTable)[tempSCName].members;

      bool varInSuperClass = ((*localClassMem).count(nodeId) == 1);

      if (varInSuperClass)
      {
        isLegal = true;
        variableInfo = (*localClassMem)[nodeId];
        break;
      }
      else
      {
        tempSCName = (*this->classTable)[tempSCName].superClassName;
      }
    }
  }

  node->objectClassName = variableInfo.type.objectClassName; //Back the way before the traverse
  node->basetype = variableInfo.type.baseType;               //Back the way before the traverse

  if (!isLegal)
  {
    // std::cout<<"TEST"
    typeError(undefined_variable);
  }

}

void TypeCheck::visitIntegerLiteralNode(IntegerLiteralNode *node)
{
  node->visit_children(this);

  node->basetype = bt_integer;
  // std::cout << "visitIntegerLiteralNode\n";
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitBooleanLiteralNode(BooleanLiteralNode *node)
{
  node->visit_children(this);

  node->basetype = bt_boolean;
  // std::cout << "visitBooleanLiteralNode" << node->integer->value << "\n";
  // std::cout << node->integer->value << "\n";
}

void TypeCheck::visitNewNode(NewNode *node)
{
  node->visit_children(this);

  
  if (this->classTable->count(node->identifier->name) == 1){
    typeError(undefined_class);
  }

  node->basetype = bt_object;
  node->objectClassName = node->identifier->name;
}

void TypeCheck::visitIntegerTypeNode(IntegerTypeNode *node)
{
  node->visit_children(this);

  node->basetype = bt_integer;
}

void TypeCheck::visitBooleanTypeNode(BooleanTypeNode *node)
{
  node->visit_children(this);

  node->basetype = bt_boolean;
}

void TypeCheck::visitObjectTypeNode(ObjectTypeNode *node)
{
  // WRITEME: Replace with code if necessary
  node->basetype = bt_object;
  node->objectClassName = node->identifier->name;
  // // std::cout << "ppp "<< node->identifier->name <<"\n";
}

void TypeCheck::visitNoneNode(NoneNode *node)
{
  node->visit_children(this);

  // std::cout<<"NONE --"<< node->basetype << "\n";
  node->basetype = bt_none;
}

void TypeCheck::visitIdentifierNode(IdentifierNode *node)
{
  node->visit_children(this);
  node->basetype = bt_none;
}

void TypeCheck::visitIntegerNode(IntegerNode *node)
{
  node->visit_children(this);
  node->basetype = bt_integer;
}

// The following functions are used to print the Symbol Table.
// They do not need to be modified at all.

std::string genIndent(int indent)
{
  std::string string = std::string("");
  for (int i = 0; i < indent; i++)
    string += std::string(" ");
  return string;
}

std::string string(CompoundType type)
{
  switch (type.baseType)
  {
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

void print(VariableTable variableTable, int indent)
{
  std::cout << genIndent(indent) << "VariableTable {";
  if (variableTable.size() == 0)
  {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (VariableTable::iterator it = variableTable.begin(); it != variableTable.end(); it++)
  {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << string(it->second.type);
    std::cout << ", " << it->second.offset << ", " << it->second.size << "}";
    if (it != --variableTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(MethodTable methodTable, int indent)
{
  std::cout << genIndent(indent) << "MethodTable {";
  if (methodTable.size() == 0)
  {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (MethodTable::iterator it = methodTable.begin(); it != methodTable.end(); it++)
  {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    std::cout << genIndent(indent + 4) << string(it->second.returnType) << "," << std::endl;
    std::cout << genIndent(indent + 4) << it->second.localsSize << "," << std::endl;
    print(*it->second.variables, indent + 4);
    std::cout << std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --methodTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(ClassTable classTable, int indent)
{
  std::cout << genIndent(indent) << "ClassTable {" << std::endl;
  for (ClassTable::iterator it = classTable.begin(); it != classTable.end(); it++)
  {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    if (it->second.superClassName != "")
      std::cout << genIndent(indent + 4) << it->second.superClassName << "," << std::endl;
    print(*it->second.members, indent + 4);
    std::cout << "," << std::endl;
    print(*it->second.methods, indent + 4);
    std::cout << std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --classTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}" << std::endl;
}

void print(ClassTable classTable)
{
  print(classTable, 0);
}
