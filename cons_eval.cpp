#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CallGraph.h"
#include <string>

#include "llvm/IR/LegacyPassManager.h"
// #define pfel(i) errs() << "" << ""
// #define pf(i) errs() << ""
#define pfel(i) errs() << i << "\n"
#define pf(i) errs() << i
#define pfvar(i) errs() << "%" << i
#define getnamefo(Si) Si->getPointerOperand()->getName().str()
using namespace std;
// macro for print the Value" type of data we get from getoperand() function
#define pfop(operand)                                                          \
  operand->print(llvm::outs());                                                \
  llvm::outs();
#define pfopel(operand)                                                        \
  operand->print(llvm::outs());                                                \
  llvm::outs() << "\n";
// #define out(i) outfile << i
// #define outel(i) outfile << i<<"\n";

using namespace llvm;
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <bits/stdc++.h>
#include <iostream>
ofstream outfile;
/*
identify itr function then update the value of the

Storeinst:
getoperand[0] //value this is either data or operand getvalue
getoperand[1] //destination pointer of the destination variable getpointer
operand

*/
map<string,map<string,string>> callsite;
map<Instruction *,int> insttoLine;
std::string stripmod(std::string var) {
  if (var[0] == '%') {
    std::string var2(var.begin() + 1, var.end());
    return var2;
  } else
    return var;
}

std::string addmod(std::string var) {
  if (var.at(0) == '%')
    return var;
  std::string s = "%";
  return s.append(var);
}
void iterateME(Instruction *i) {
  unsigned numOperands = i->getNumOperands();

  for (unsigned ii = 0; ii < numOperands; ++ii) {
    Value *operand = i->getOperand(ii);
    // pfel(operand->print());
    pf("\nindex :");
    pfel(ii);
    pf("operand type:");
    pfopel(operand->getType());
    pf("Plain operand :");
    pfopel(operand);
    pfel("----------------------");
  }
}
void iterateCallGraph(const std::map<std::string, std::vector<std::string>>& mycallgraph) {
    // Iterate over each entry in the map
    for (const auto& entry : mycallgraph) {
        std::cout << "Function: " << entry.first << std::endl;
        
        // Iterate over each function called by the current function
        for (const auto& callee : entry.second) {
            std::cout << "  Calls: " << callee << std::endl;
        }
    }
}
std::string getStringFromInstruction(Instruction *inst) {
  // Instruction *inst = /* your instruction */;

  // Create a raw string output stream
  std::string str;
  llvm::raw_string_ostream stream(str);

  // Print the instruction to the string stream
  inst->print(stream);

  // Get the string representation of the instruction
  std::string instStr = stream.str();
  return instStr;
  // Print the string representation of the instruction
  // llvm::outs() << "Instruction: " << instStr << "\n";
}
string getStringfromVal(Value *v)
{
  string s;
  raw_string_ostream os(s);
  v->printAsOperand(os, false);
  os.flush();
  std::string instructionSubstr = os.str();
  return instructionSubstr;
}

std::string getresultOperand(Instruction *i) {
  std::string s;
  raw_string_ostream os(s);
  i->printAsOperand(os, false);
  os.flush();
  std::string instructionSubstr = os.str();
  return instructionSubstr;
}
string getValueAfterPipe(const std::string& input) {
    // Find the position of the '|' character
    size_t pipePos = input.find('|');

    // If '|' is not found or it is the last character, return an empty string
    if (pipePos == std::string::npos || pipePos == input.length() - 1) {
        return "";
    }

    // Extract the substring after '|'
    return input.substr(pipePos + 1);
}
std::string getVariableNamefromoperand(Value *i) {
  if (llvm::ConstantInt *constantint = llvm::dyn_cast<llvm::ConstantInt>(i)) {

    // pfel("value is constant");
    int value = constantint->getSExtValue();
    return std::to_string(value);
    ;
    pf(value);
    pf("\n");
  } else {
    // pfel("value is variable!!!");

    // Check if the stored value is an instruction
    if (Instruction *storedInstruction = dyn_cast<Instruction>(i)) {

      // Get the name of the variable from the instruction
      std::string variableName = storedInstruction->getName().str();

      // Print the name of the variable
      
      pfel("HMMMMMMMM" << getresultOperand(storedInstruction));
      pfvar(variableName);
      pf("\n");
      return getresultOperand(storedInstruction);
      return variableName;
      // outs() << "Variable name: " << variableName << "\n";
    } else {
      // The stored value is not an instruction
      pf("Stored value is not an instruction.\n");
      return "MID";
    }
  }
}

void printMapValues(const std::map<std::string, std::string> &myMap) {
  pf("Values in the map:\n\t\t");

  for (const auto &pair : myMap) {
    pf("(" << pair.first << ":" << pair.second << ") ");
    // std::cout << pair.second << std::endl;
  }
}

std::vector<std::string> findSuccessors(Instruction *Inst) {
  std::vector<std::string> successorList;
  // if (!I)
  //   return;
  BasicBlock *BB = Inst->getParent();
  for (BasicBlock *Successor : successors(BB)) {
    // Do something with the successor
    // BasicBlock *Succ = Inst.getSuccessor(i);
    successorList.push_back(
        getStringFromInstruction(dyn_cast<Instruction>(Successor->begin())));
  }

  pf(getStringFromInstruction(Inst)
     << "sizeeeeeeeeeeEE:::::::::::" << successorList.size());
  return successorList;
}

void iterateVector(const std::vector<std::string> &vec) {
  for (const std::string &str : vec) {
    pf(str << " ");
    // std::cout << str << std::endl;
  }
  pf("\n");
}
bool isInteger(const std::string &str) {
  if (str.empty() ||
      ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) {
    return false;
  }

  char *p;
  strtol(str.c_str(), &p, 10);

  return (*p == 0);
}

int stringToInt(const std::string &str) {
  if (!isInteger(str)) {
    // Handle error or return a default value
    // std::cerr << "Invalid integer string: " << str << std::endl;
    return 0; // Default value
  }

  int intValue;
  std::istringstream iss(str);
  iss >> intValue;
  return intValue;
}

// take two stirgs and give out the meet of these two strings
std::string meetValue(std::string val1, std::string val2) {
  if (isInteger(val1) && isInteger(val2)) {
    // both are contant and equal therefore meet is contant value
    if (stringToInt(val1) == stringToInt(val2)) {
      return val1;
    } else {
      return "BOTTOM";
    }
  } else {
    if (val1 == "BOTTOM" || val2 == "BOTTOM") {
      return "BOTTOM";
    } else // either one is top
    {
      // return TOP in the val1/2 if false or returns constant value from val1/2
      return isInteger(val1) ? val1 : val2;
    }
  }
}

// To Do check this functionatlity
//  take two maps and calculates the meet of these two maps
//  x meet top = x
//  c1 meet c2 = bottom
//  x meet botom =bottom
std::map<std::string, std::string>
meet(std::map<std::string, std::string> tuple1,
     std::map<std::string, std::string> tuple2) {
  // pf("in meet");
  std::map<std::string, std::string> newtuple;

  for (auto i = tuple1.begin(); i != tuple1.end(); i++) {

    // same variable exits in both
    if (tuple2.find(i->first) != tuple2.end()) {
      // pf(i->first << ":" << i->second << "|-|" << tuple2.find(i->first))
      //     ->second;
      newtuple[i->first] = meetValue(i->second, tuple2.find(i->first)->second);
      // pfel("=" << newtuple[i->first]);

    } else {
      // copy variable as it is
      newtuple[i->first] = i->second;
    }
  }
  for (auto i = tuple2.begin(); i != tuple2.end(); i++) {
    // if it doesnt exist add it as it is
    if (tuple1.find(i->first) == tuple1.end()) {
      newtuple[i->first] = i->second;
    }
  }

  return newtuple;
}

bool mapChanged(const std::map<std::string, std::string> &map1,
                const std::map<std::string, std::string> &map2) {
  if (map1.size() != map2.size()) {
    return true; // Maps have different sizes
  }

  for (const auto &pair : map1) {
    auto it = map2.find(pair.first);
    if (it == map2.end() || it->second != pair.second) {
      return true; // Element not found in map2 or values are different
    }
  }

  return false; // Maps are equal
}

void printQueue(std::queue<std::string> gq) {
  std::queue<std::string> g = gq;
  while (!g.empty()) {
    // cout << '\t' << g.front();
    pf(g.front() << " \n");
    g.pop();
  }
  // cout << '\n';
  pf("\n");
}

// function takes input as instruction and also map of the current point
// std::map<std::string,Instruction *> getInstructionFromString;

std::map<std::string, std::string>
transferFunc(
             //std::string curInstructionStr,
             std::map<std::string, std::string> curMap,
             //std::map<std::string, Instruction *> getInstructionFromString,
             Instruction *ist) {
  // pf("\ngot ins is" << *ist << "\n");

  // need to update the curMap values in this one first;
  std::map<std::string, std::string> newMap;
  for (const auto &pair : curMap) {
    newMap.insert(pair);
  }
  // Instruction *inst=getInstructionFromString[curInstructionStr];
  // inst->getOpcode();

  switch (ist->getOpcode()) {
  default:
    break;

  case Instruction::Alloca: {
    pf("\t\tAlloca Instructino in "
       "FUNCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
    pf(*ist);
    std::string instructionSubstr =
        getresultOperand(dyn_cast<Instruction>(ist));
    // instructionSubstr is always stripped of % by default so add %
    // instructionSubstr = addmod(instructionSubstr);
    pfel(" --> " << instructionSubstr << " = TOP");
    newMap[instructionSubstr] = "TOP";
    break;
  }
  case Instruction::Load: {
    pf("\t\tLoadddd Instruction\n");
    if (LoadInst *LI = dyn_cast<LoadInst>(ist)) {
      std::string s;

      raw_string_ostream os(s);
      LI->printAsOperand(os, false);
      os.flush();
      std::string instructionSubstr = os.str();
      pf(*LI);
      std::string variableName = LI->getPointerOperand()->getName().str();
      unsigned numOperands = LI->getNumOperands();
      pfel("-->" << instructionSubstr << " = " << variableName);

      // update from here
      // variable always has mode in load
      // instructionSubstr = addmod(instructionSubstr);

      // variableName=addmod(variableName);
      string destinationOpernad = instructionSubstr;
      if (isInteger(destinationOpernad)) {
        newMap[instructionSubstr] = destinationOpernad;

      } else {
        pf("checkkkkkkkkk " << curMap[addmod(variableName)] << " "
                            << addmod(variableName));
        newMap[instructionSubstr] = curMap[addmod(variableName)];
      }
    }
    break;
  }
  case Instruction::Store: {
    pf("\t\tStore Instruction\n");
    if (StoreInst *Si = dyn_cast<StoreInst>(ist)) {

      pfel(" " << *ist << " ");

      unsigned numOperands = Si->getNumOperands();

      std::string variableName = Si->getPointerOperand()->getName().str();
      Value *storedValue = Si->getValueOperand();

      // pfel("1st operand/variable name :");
      pf("-->");
      variableName = addmod(variableName);

      pf(variableName << " = ");
      string destinationOpernad = getVariableNamefromoperand(storedValue);
      pfel(destinationOpernad<<"?????????????????????????????");
      // val is int assign it to variable
      if(destinationOpernad=="MID")
      {
        pfel("try"<<getStringfromVal(storedValue)<<"-"<<stripmod(getStringfromVal(storedValue)));
        pfel("got"<<curMap[getStringfromVal(storedValue)]<<"-"<<curMap[stripmod(getStringfromVal(storedValue))]);
        
        if(curMap[getStringfromVal(storedValue)]=="")
        newMap[variableName]="TOP";
        else if(curMap.find(getStringfromVal(storedValue))!=curMap.end()
          && curMap[getStringfromVal(storedValue)]!="BOTTOM"
        )
        newMap[variableName] = curMap[getStringfromVal(storedValue)];
        else
        pfel("NOT found passed params");

      }else
      if (isInteger(destinationOpernad)) {
        pfel("this is in store in instruction"<<variableName<<"="<<destinationOpernad);
        newMap[variableName] = destinationOpernad;

      }else if(curMap.find(destinationOpernad)!=curMap.end())
      {
        pfel(variableName<<">>"<<curMap[destinationOpernad]);
        newMap[variableName]=curMap[destinationOpernad];
      }
       else {
        newMap[variableName] =
            meetValue(curMap[variableName], destinationOpernad);
        // newMap[variableName] =
        // curMap[getVariableNamefromoperand(storedValue)];
      }
    }
    break;
  }
  case Instruction::GetElementPtr: {
    pf("\t\t GET element\n");
    break;
  }

  case Instruction::Call: {

    pfel("call instruciton"<<*ist);
    
    if (CallInst *Si = dyn_cast<CallInst>(ist)) {
      Function *CalledFunc = Si->getCalledFunction();
      if(CalledFunc->getName().str()=="printf" )
      {
        pfel("Printf/scanf");
      }else if(CalledFunc->getName().str()=="__isoc99_scanf")
      {
        newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";
      }else
      {
        for (Argument &arg : CalledFunc->args()) {
          // Print argument name and type
          string argumentStr=arg.getName().str();
          argumentStr=addmod(argumentStr);
          pfel("Argument name: " << argumentStr << ", Argument type: " << *arg.getType() );
          pfel(getStringfromVal(Si->getOperand(arg.getArgNo()))<<"retrieved value for "<<argumentStr);
            

          
          Value *callargs=Si->getArgOperand(arg.getArgNo());
          // pfel("somehting"<<callargs->getName());
          // pfel(getresultOperand(dyn_cast<Instruction>(callargs)));
          // callargs->printAsOperand(errs());
          
          if (isa<ConstantInt>(callargs)) {
            ConstantInt *CI = cast<ConstantInt>(callargs);
            errs() << "Parameter " << arg.getArgNo() << ": " << CI->getSExtValue() << "\n";
            
          }
          //this is for the constants that are propagated a=10 and a is paramm 
          //then update the callsite with this param
          // 
          else
          {
            pfel("string instruction"<<getStringFromInstruction(dyn_cast<Instruction>(ist)));
            // iterateFuncMap(valueTupleforFunction[CalledFunc->getName().str()]);
            
            // printMapValues(valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))]);
            // string retrieved_val=valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))][getStringfromVal(Si->getOperand(arg.getArgNo()))];
            string retrieved_val=curMap[getStringfromVal(Si->getOperand(arg.getArgNo()))];
            pfel("Transfer func intra const val"<<retrieved_val);
            callsite[CalledFunc->getName().str()][argumentStr]=retrieved_val;
            callsite[to_string(insttoLine[dyn_cast<Instruction>(ist)])+"|"+CalledFunc->getName().str()][argumentStr]=retrieved_val;
            
          }
        }
          pfel("something elseeeee");







        // map<string,string>meetofcalls;
        // callsite[CalledFunc->getName().str()]=meet(callsite[CalledFunc->getName().str()],meetofcalls);

        // map<string,string>meetofcalls;
        string keyfuncname=to_string(insttoLine[dyn_cast<Instruction>(ist)])+"|"+CalledFunc->getName().str();

        pfel("\nGENERIC CALL for"<<CalledFunc->getName().str());
        printMapValues(callsite[CalledFunc->getName().str()]);
        pfel("\nSPECFIC THING"<<keyfuncname);
        printMapValues(callsite[keyfuncname]);

        pfel("\nBRR"<<insttoLine[dyn_cast<Instruction>(ist)]<<" official"<<keyfuncname);
        callsite[CalledFunc->getName().str()]=meet(callsite[CalledFunc->getName().str()],callsite[keyfuncname]);

        
        // pfel("BRRR"<<insttoLine[dyn_cast<Instruction>(ii)]<<" official"<<to_string(insttoLine[dyn_cast<Instruction>(ii)])+"|"+CalledFunc->getName().str());
        pfel("\nNEW vals for "<<CalledFunc->getName().str());
        printMapValues(callsite[CalledFunc->getName().str()]);
        //update the callsite[keyfuncname] with the constants if the variable has constant values 
        // callsite[curCall] this values you have to update
        
        // updateMap(callsite[keyfuncname],callsite[curCall]);
        
        // pfel("new valssssss");
        // printMapValues(callsite[keyfuncname]);
      }
      
      // linetoInst[ii];
      // insttoLine[ii];
      // ii->eraseFromParent();

      
    }
    
    
    //-----------------------------------------------
    // if (CallInst *Si = dyn_cast<CallInst>(ist)) {
    //   // iterateME(Si);

    //   Function *CalledFunc = Si->getCalledFunction();
    //   if (CalledFunc) {
    //       string FuncName = CalledFunc->getName().str();
    //       // outs()<<"hMM"<<FuncName<<"\n";
    //       if(FuncName=="printf"){
    //       // outs()<<"breaking stufff";
    //       break;
    //       }else if(CalledFunc->getName().str()=="__isoc99_scanf")
    //       {
    //         newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";
    //       }else
    //       {
    //         map<string,string>meetofcalls;
    //         callsite[CalledFunc->getName().str()]=meet(callsite[CalledFunc->getName().str()],meetofcalls);
    //         // outs()<<getVariableNamefromoperand(Si->getOperand(1))<<"IS BOTTTTTTTTT";
    //       }

          

    //       // return FuncName.equals("printf") || FuncName.equals("scanf");
    //   }
    // }
    break;
  }
  case Instruction::ICmp:
  case Instruction::Ret:
  case Instruction::Br:
  case Instruction::Invoke: {
    break;
  }

  // Binary Instructions
  case Instruction::Add:
  case Instruction::Sub:
  case Instruction::Mul:
  case Instruction::SDiv:
  case Instruction::UDiv:
  case Instruction::SRem:
  case Instruction::URem:
  case Instruction::Shl:
  case Instruction::LShr:
  case Instruction::AShr:
  case Instruction::And:
  case Instruction::Or:
  case Instruction::Xor: {
    pfel("\t\tBinary Instruction\n" << *ist);
    // iterateME(dyn_cast<Instruction>(i));
    string resultOperand, stringOp1, stringOp2;

    resultOperand = (getresultOperand(dyn_cast<Instruction>(ist)));
    stringOp1 = (getVariableNamefromoperand(ist->getOperand(0)));
    stringOp2 = (getVariableNamefromoperand(ist->getOperand(1)));
    pf(resultOperand << "= ");
    int op1, op2;

    if ((isInteger(stringOp1) && isInteger(stringOp2))) {
      op1 = stringToInt(stringOp1);
      op2 = stringToInt(stringOp1);
      switch (ist->getOpcode()) {
      default:
        break;
      case Instruction::Add: {
        newMap[resultOperand] = std::to_string(op1 + op2);
        break;
      }
      case Instruction::Sub: {
        newMap[resultOperand] = std::to_string(op1 - op2);
        break;
      }
      case Instruction::Mul: {
        newMap[resultOperand] = std::to_string(op1 * op2);
        break;
      }
      case Instruction::SDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
      case Instruction::UDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
      }
      // switch case execute operation
      // switch (ist->getOpcode()) {
      // default:
      //   break;
      // case Instruction::Add: {
      //   newMap[resultOperand] = std::to_string(op1 + op2);
      //   break;
      // }
      // case Instruction::Sub: {
      //   newMap[resultOperand] = std::to_string(op1 - op2);
      //   break;
      // }
      // case Instruction::Mul: {
      //   newMap[resultOperand] = std::to_string(op1 * op2);
      //   break;
      // }
      // case Instruction::SDiv: {
      //   newMap[resultOperand] = std::to_string(op1 / op2);
      //   break;
      // }
      // case Instruction::UDiv: {
      //   newMap[resultOperand] = std::to_string(op1 / op2);
      //   break;
      // }
      // case Instruction::SRem:
      // case Instruction::URem:
      // case Instruction::Shl:
      // case Instruction::LShr:
      // case Instruction::AShr:
      // case Instruction::And:
      // case Instruction::Or:
      // case Instruction::Xor:
      // }

    } else if (isInteger(curMap[stringOp1]) && isInteger(curMap[stringOp2])) {
      op1 = stringToInt((curMap[stringOp1]));
      op2 = stringToInt((curMap[stringOp2]));

      // // switch case execute operation
      switch (ist->getOpcode()) {
      default:
        break;
      case Instruction::Add: {
        newMap[resultOperand] = std::to_string(op1 + op2);

        break;
      }
      case Instruction::Sub: {
        newMap[resultOperand] = std::to_string(op1 - op2);
        break;
      }
      case Instruction::Mul: {
        newMap[resultOperand] = std::to_string(op1 * op2);
        break;
      }
      case Instruction::SDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
      case Instruction::UDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
        // case Instruction::SRem:
        // case Instruction::URem:
        // case Instruction::Shl:
        // case Instruction::LShr:
        // case Instruction::AShr:
        // case Instruction::And:
        // case Instruction::Or:
        // case Instruction::Xor:
      }
      // newMap[resultOperand] =
      // curMap[getVariableNamefromoperand(storedValue)];
    } else if (curMap[stringOp1] == "BOTTOM" || curMap[stringOp2] == "BOTTOM") {
      newMap[resultOperand] = "BOTTOM";

    } else if (isInteger(curMap[stringOp1]) && isInteger(stringOp2)) {
      pf("VALUE AND OPERANDS ARE HERE :"
         << "key" << stringOp1 << "val:" << curMap[stringOp1]);
      op1 = stringToInt(curMap[stringOp1]);
      op2 = stringToInt(stringOp2);
      switch (ist->getOpcode()) {
      default:
        break;
      case Instruction::Add: {
        newMap[resultOperand] = std::to_string(op1 + op2);

        break;
      }
      case Instruction::Sub: {
        newMap[resultOperand] = std::to_string(op1 - op2);
        break;
      }
      case Instruction::Mul: {
        newMap[resultOperand] = std::to_string(op1 * op2);
        break;
      }
      case Instruction::SDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
      case Instruction::UDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
        // case Instruction::SRem:
        // case Instruction::URem:
        // case Instruction::Shl:
        // case Instruction::LShr:
        // case Instruction::AShr:
        // case Instruction::And:
        // case Instruction::Or:
        // case Instruction::Xor:
      }

    } else if (isInteger(curMap[stringOp2]) && isInteger(stringOp1)) {
      pf("VALUE AND OPERANDS ARE HERE :"
         << "key" << stringOp2 << "val:" << curMap[stringOp2] << "ope2"
         << stringOp1);
      op2 = stringToInt(curMap[stringOp2]);
      op1 = stringToInt(stringOp1);
      switch (ist->getOpcode()) {
      default:
        break;
      case Instruction::Add: {
        newMap[resultOperand] = std::to_string(op1 + op2);

        break;
      }
      case Instruction::Sub: {
        newMap[resultOperand] = std::to_string(op1 - op2);
        break;
      }
      case Instruction::Mul: {
        newMap[resultOperand] = std::to_string(op1 * op2);
        break;
      }
      case Instruction::SDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
      case Instruction::UDiv: {
        newMap[resultOperand] = std::to_string(op1 / op2);
        break;
      }
        // case Instruction::SRem:
        // case Instruction::URem:
        // case Instruction::Shl:
        // case Instruction::LShr:
        // case Instruction::AShr:
        // case Instruction::And:
        // case Instruction::Or:
        // case Instruction::Xor:
      }

    } else {
      newMap[resultOperand] = "TOP";
    }
    // one more condition of cannot be evaluted

    // pf("\t\ttesttt\t\t");
    // pfopel(i->getOperand(0));

    pf(getVariableNamefromoperand(ist->getOperand(0)) << "= ");
    pf(getVariableNamefromoperand(ist->getOperand(1)) << "= ");
    pf("OUT=" << newMap[resultOperand]);

    break;
  }
  }

  return newMap;
}
std::map<std::string, std::map<std::string, std::string>> kildalls(Function &F,string curCall="") {
    int linenumber = 0;
    // std::map<std::string, Instruction> linemap;

    // maintain worklist which is nothing but the instruction as string

    // every basic block has unique name and every basic block should have a
    // map to store the changes in the data values after map
    std::map<std::string, std::map<std::string, std::string>> valueTuple;

    std::map<std::string, std::vector<std::string>> successor;
    std::map<std::string, Instruction *> getInstructionFromString;
    // std::map<Instruction, int> tst;
    // std::map<Instruction *, std::map<std::string, int>> gmap;
    bool flag=0;

    for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) {
      for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2; i++) {

        if(flag==0)
        {
          flag=1;
          string keyfuncname=to_string(insttoLine[dyn_cast<Instruction>(i)])+"|"+F.getName().str();
          if(curCall!="")
          {
            pfel("enter the dragon "<<curCall);

            //have to check this maybe perform meet
            callsite[getValueAfterPipe(curCall)]=meet(callsite[getValueAfterPipe(curCall)],callsite[curCall]);
            valueTuple[getStringFromInstruction(dyn_cast<Instruction>(i))]=callsite[getValueAfterPipe(curCall)];
            pfel("MEET of"<<getValueAfterPipe(curCall)<<" & "<<curCall);
            printMapValues(callsite[getValueAfterPipe(curCall)]);
            pfel("lets go?"); 
            // printMapValues(valueTuple[getStringFromInstruction(dyn_cast<Instruction>(i))]);
          }
        }

        // add all the instruction in the worklist queue
        // worklist.push(getStringFromInstruction(dyn_cast<Instruction>(i)));
        // isChanged[getStringFromInstruction(dyn_cast<Instruction>(i))] =
        // false; visited[getStringFromInstruction(dyn_cast<Instruction>(i))] =
        // false; getInstructionFromString[getStringFromInstruction(
        //     dyn_cast<Instruction>(i))] = dyn_cast<Instruction>(i);
        // pf("HERE WE GO AGAIN \n\n\n\n\n"
        //    << *getInstructionFromString[getStringFromInstruction(
        //           dyn_cast<Instruction>(i))]);
        // pf("Getting the
        // instruction\n\n"<<getStringFromInstruction(getInstructionFromString[getStringFromInstruction(dyn_cast<Instruction>(i))]));
        // pfop(getInstructionFromString[getStringFromInstruction(dyn_cast<Instruction>(i))]);

        if (dyn_cast<Instruction>(i) == bb->getTerminator()) {
          // pf(getStringFromInstruction(dyn_cast<Instruction>(i))
          //    << "this is last node of block ");
          successor[getStringFromInstruction(dyn_cast<Instruction>(i))] =
              findSuccessors(dyn_cast<Instruction>(i));
          iterateVector(findSuccessors(dyn_cast<Instruction>(i)));
          pf("---\n");

        } else {
          // consecutive instruction in the basic block have next instruction as
          // successor
          std::vector<std::string> v;
          v.push_back(getStringFromInstruction(
              dyn_cast<Instruction>(i->getNextNode())));
          successor[getStringFromInstruction(dyn_cast<Instruction>(i))] = v;

          // pfel("\n"
          //      << getStringFromInstruction(dyn_cast<Instruction>(i)) <<
          //      "---->"
          //      << getStringFromInstruction(
          //             dyn_cast<Instruction>(i->getNextNode()))
          //      << " \n");
        }
      }
    }
    // pf("below is worklist\n\n");
    // printQueue(worklist);
    // pf("\n\n");
    bool Changed = false;
    int count = 0;

    // do while
    do {
      // if (count-- )
      //   break;

      std::queue<std::string> worklist;
      // std::queue<Instruction*> worklist2;
      // std::map<std::string, bool> isChanged;
      std::map<std::string, bool> visited;
      std::map<std::string, bool> inQ;
      Changed = false;

      for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) {
        for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;
             i++) {

          // add all the instruction in the worklist queue
          if (worklist.empty())
            worklist.push(getStringFromInstruction(dyn_cast<Instruction>(i)));
          // isChanged[getStringFromInstruction(dyn_cast<Instruction>(i))] =
          // false;
          visited[getStringFromInstruction(dyn_cast<Instruction>(i))] = false;
          inQ[getStringFromInstruction(dyn_cast<Instruction>(i))] = false;
          getInstructionFromString[getStringFromInstruction(
              dyn_cast<Instruction>(i))] = dyn_cast<Instruction>(i);
        }
      }

      pfel("\t\t\t\tITERATION" << worklist.empty() << "||");

      // run while worklist is not empty
      while (!worklist.empty()) {
        pfel("\n\n");

        std::string curInstructionStr = worklist.front();
        // if()
        worklist.pop();
        // pfel("current instruction");
        // pfel("--------------<" << curInstructionStr << ">");
        visited[curInstructionStr] = true;
        std::map<std::string, std::string> curMap =
            valueTuple[curInstructionStr];

        // get Instruction type from string of instruction
        // pf("retrived instruction"
        //    << *getInstructionFromString[curInstructionStr]);
        // Instruction *ist=getInstructionFromString[curInstructionStr]);

        // we pass instruction
        // map<string, string> newMap =
        //     transferFunc(curInstructionStr, curMap, getInstructionFromString,
        //                  getInstructionFromString[curInstructionStr]);

        map<string, string> newMap =
            transferFunc(curMap,
                         getInstructionFromString[curInstructionStr]);

        // if (mapChanged(newSuccessorMap, valueTuple[curr_successors[i]])) {
        if (mapChanged(newMap, curMap)) {
            pfel("map are changed");
            Changed = true;
          } else {
            pfel("NOT Changed");
          }

        pfel("print current map");
        printMapValues(curMap);

        pfel("\nupdated map after transfer function");
        printMapValues(newMap);
        // pfel("after map print+++++++++++++++++++++");
        // update the current map
        valueTuple[curInstructionStr] = newMap;

        vector<string> curr_successors = successor[curInstructionStr];

        for (size_t i = 0; i < curr_successors.size(); ++i) {
          pfel("\nsuccessor " << i << ":" << curr_successors[i]);
          if (visited[curr_successors[i]]) {
            pfel("visited successor" << visited[curr_successors[i]] << "|");
            continue;
          }
          // udpate the successors map
          // std::map<std::string, std::map<std::string, std::string>> valueTuple;

          // map<string, string> newSuccessorMap = meet(
          //     valueTuple[curr_successors[i]], 
          //     transferFunc(curr_successors[i], valueTuple[curInstructionStr], getInstructionFromString,
          //                getInstructionFromString[curr_successors[i]])
          //     );

          map<string, string> newSuccessorMap = meet(
              valueTuple[curr_successors[i]], valueTuple[curInstructionStr]);

          

          pf("OLD values of successor");
          printMapValues(valueTuple[curr_successors[i]]);

          pf("\nNEW values of successor");
          printMapValues(newSuccessorMap);

          valueTuple[curr_successors[i]] = newSuccessorMap;

          if (!inQ[curr_successors[i]] && Changed) {
            worklist.push(curr_successors[i]);
            inQ[curr_successors[i]] = true;
          }
        }

        // break;
        // get instruction from work list
        // mark it as visited
        // apply transfer function
        // All meet of the current map to all the successor nodes maps
        // unless already visited
        // check with the pervious values of the map and check if the current
        // ones are different if yes then set chagned to true
        // add the changes instruction in to the worklist
        /* code */
        pf("\nbelow is worklist\n\n");
        printQueue(worklist);
        pf("\n\n");
      }

    } while (Changed == true);

    std::error_code EC;
    string filename = __FILE__;
    size_t dotPosition = filename.find_last_of('.');

    // Remove the extension (including the dot)
    std::string filenameWithoutExtension = filename.substr(0, dotPosition);

    // Append the new extension
    std::string newFilename = filenameWithoutExtension + ".txt";

    // filename.at()
    raw_fd_ostream outFile("cool", EC);
    pf("outfile is"<<newFilename);
    // outFile << "THIS IS CRI"
    //         << "\n";

    // outFile<<F.getName().str()<<"\n";

    // for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) {

    //   // std::string curr_block=bb->getName()  ;
    //   // std::string curr_block_name(bb->getName().data(),
    //   // bb->getName().size()); errs() << "BB name " << curr_block_name << "\n";

    //   // errs() << "BB size " << bb->size() << "\n";
    //   for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2; i++) {
    //     // pfel("\t\t\t||| " << *i << "\t\t\t |||");
    //     outFile << *i << " ";
    //     outs()<<*i << " ";
    //     // Instruction lineinstruction=dyn_cast<Instruction> (i);
    //     // linemap[linenumber++]=* i;
    //     // worklist.push(getStringFromInstruction(dyn_cast<Instruction>(i)));

    //     switch (i->getOpcode()) {
    //     default:
    //       break;

    //     case Instruction::Alloca: {
    //       // pf("\t\tAlloca Instructino\n");
    //       // pf(*i);

    //       std::string instructionSubstr =
    //           getresultOperand(dyn_cast<Instruction>(i));
    //       // pfel(" --> " << stripmod(instructionSubstr) << " = TOP");
    //       outFile << " --> " << addmod(instructionSubstr) << " = TOP";
    //       outFile << "\n";
    //       outs() << " --> " << addmod(instructionSubstr) << " = TOP";
    //       outs() << "\n";
    //       break;
    //     }
    //     case Instruction::Load: {
    //       pf("\t\tLoadddd Instruction\n");
    //       if (LoadInst *LI = dyn_cast<LoadInst>(i)) {
    //         std::string s;

    //         raw_string_ostream os(s);
    //         LI->printAsOperand(os, false);
    //         os.flush();
    //         std::string instructionSubstr = os.str();
    //         pf(*LI);
    //         std::string variableName = LI->getPointerOperand()->getName().str();
    //         unsigned numOperands = LI->getNumOperands();
    //         pfel("-->" << instructionSubstr << " = " << variableName);
    //         outFile << "-->" << addmod(instructionSubstr) << " = "
    //                 << valueTuple[getStringFromInstruction(
    //                        dyn_cast<Instruction>(i))][addmod(variableName)];
    //         outFile << "\t" << addmod(variableName) << " = "
    //                 << valueTuple[getStringFromInstruction(
    //                        dyn_cast<Instruction>(i))][addmod(variableName)];
    //         outs() << "-->" << addmod(instructionSubstr) << " = "
    //                 << valueTuple[getStringFromInstruction(
    //                        dyn_cast<Instruction>(i))][addmod(variableName)];
    //         outs() << "\t" << addmod(variableName) << " = "
    //                 << valueTuple[getStringFromInstruction(
    //                        dyn_cast<Instruction>(i))][addmod(variableName)];
    //         // std::string instructionSubstr =
    //         //         getresultOperand(dyn_cast<Instruction>(ist));
    //         //     // instructionSubstr is always stripped of % by default so
    //         //     add %
    //         //     // instructionSubstr = addmod(instructionSubstr);
    //         //     pfel(" --> " << instructionSubstr << " = TOP");
    //         //     newMap[instructionSubstr] = "TOP";
    //         // update from here
    //         // variable always has mode in load
    //         // instructionSubstr = addmod(instructionSubstr);

    //         // variableName=addmod(variableName);
    //         // string destinationOpernad = instructionSubstr;
    //         // if (isInteger(destinationOpernad)) {
    //         //   newMap[instructionSubstr] = destinationOpernad;

    //         // } else {
    //         //   pf("checkkkkkkkkk " << curMap[addmod(variableName)] << " "
    //         //                       << addmod(variableName));
    //         //   newMap[instructionSubstr] = curMap[addmod(variableName)];
    //         // }
    //         outFile << "\n";
    //         outs()<<"\n";
    //       }

    //       break;
    //     }
    //     case Instruction::Store: {
    //       pf("\t\tStore Instruction\n");
    //       if (StoreInst *Si = dyn_cast<StoreInst>(i)) {

    //         // errs() << " " << *ist << " ";
    //         pfel("STOREEE");

    //         unsigned numOperands = Si->getNumOperands();

    //         std::string variableName = Si->getPointerOperand()->getName().str();
    //         Value *storedValue = Si->getValueOperand();

    //         // pfel("1st operand/variable name :");
    //         pf("-->");
    //         variableName = addmod(variableName);

    //         pf(variableName << " = ");
    //         string destinationOpernad = getVariableNamefromoperand(storedValue);
    //         pfel(destinationOpernad);
    //         // val is int assign it to variable
    //         if (isInteger(destinationOpernad)) {
    //           // newMap[variableName] = destinationOpernad;
    //           outFile
    //               << "-->" << variableName << " = "
    //               << valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][addmod(destinationOpernad)];
    //           outs()
    //               << "-->" << variableName << " = "<<destinationOpernad;
    //               // << valueTuple[getStringFromInstruction(
    //               //        dyn_cast<Instruction>(i))][addmod(destinationOpernad)];

    //         } else {
    //           outFile
    //               << "-->" << variableName << " = "
    //               << valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][addmod(destinationOpernad)];

    //           outFile
    //               << "\t" << destinationOpernad << " = "
    //               << valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][addmod(destinationOpernad)];
    //           // newMap[variableName] =
    //           //     meetValue(curMap[variableName], destinationOpernad);
    //           // newMap[variableName] =
    //           // curMap[getVariableNamefromoperand(storedValue)];
    //           outFile << "\n";
    //           // outs()<<"\n";
    //           outs()
    //               << "-->" << variableName << " = "
    //               << valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][addmod(destinationOpernad)];

    //           outs()
    //               << "\t" << destinationOpernad << " = "
    //               << valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][addmod(destinationOpernad)];
    //           // newMap[variableName] =
    //           //     meetValue(curMap[variableName], destinationOpernad);
    //           // newMap[variableName] =
    //           // curMap[getVariableNamefromoperand(storedValue)];
              
    //         }outs() << "\n";
    //       }
    //       break;
    //     }
    //     case Instruction::GetElementPtr: {
    //       pf("\t\t GET element\n");
    //       break;
    //     }

    //     case Instruction::Call: {
    //       if (CallInst *Si = dyn_cast<CallInst>(i)) {
    //         Function *CalledFunc = Si->getCalledFunction();
    //   if (CalledFunc) {
    //       string FuncName = CalledFunc->getName().str();
    //       if(FuncName=="printf"){
    //         outs() << "-->"<< getVariableNamefromoperand(Si->getOperand(1))<<"="<<valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][getVariableNamefromoperand(Si->getOperand(1))] ;
          
    //       }else if(CalledFunc->getName().str()=="__isoc99_scanf"){
    //         outs() << "-->" << getVariableNamefromoperand(Si->getOperand(1))
    //                 << "=BOTTOM";
    //       }
    //       else
    //       {
    //         outs() << "-->"<< getVariableNamefromoperand(Si->getOperand(1))<<"="<<valueTuple[getStringFromInstruction(
    //                      dyn_cast<Instruction>(i))][getVariableNamefromoperand(Si->getOperand(1))] ;
    //         // outs()<<getVariableNamefromoperand(Si->getOperand(1))<<"IS BOTTTTTTTTT"
    //         // newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";
            

    //       }

    //       // return FuncName.equals("printf") || FuncName.equals("scanf");
    //   }
    //         // iterateME(Si);

    //         // errs()<<"+++"<< getVariableNamefromoperand(Si->getOperand(0));
    //         // errs()<<"++"<<getVariableNamefromoperand(Si->getOperand(1));
    //         // iterateME(Si);
    //         // pf("operand value is\n");
    //         // pfop(Si->getOperand(1));pf("\n::::");
    //         // pf(getVariableNamefromoperand(Si->getOperand(1)));
    //         outFile << "-->" << getVariableNamefromoperand(Si->getOperand(1))
    //                 << "=BOTTOM";
    //         // outs() << "-->" << getVariableNamefromoperand(Si->getOperand(1))
    //         //         << "=BOTTOM";
            
    //                 // << "=BOTTOM";
    //         // newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";
    //       }
    //       outFile << "\n";
    //       outs()<<"\n";
    //       break;
    //     }
    //     case Instruction::ICmp: {
    //       outFile << "\n";
    //       outs()<<"\n";
    //       break;
    //     }
    //     case Instruction::Ret:
    //     case Instruction::Br:
    //     case Instruction::Invoke: {
    //       break;
    //     }

    //     // Binary Instructions
    //     case Instruction::Add:
    //     case Instruction::Sub:
    //     case Instruction::Mul:
    //     case Instruction::SDiv:
    //     case Instruction::UDiv:
    //     case Instruction::SRem:
    //     case Instruction::URem:
    //     case Instruction::Shl:
    //     case Instruction::LShr:
    //     case Instruction::AShr:
    //     case Instruction::And:
    //     case Instruction::Or:
    //     case Instruction::Xor: {
    //       // outFile << getresultOperand(dyn_cast<Instruction>(i)) << "= ";
    //       // outFile << getVariableNamefromoperand(i->getOperand(0)) << "= ";
    //       // outFile << getVariableNamefromoperand(i->getOperand(1)) << "= ";

    //       string op1, op2;
    //       op1 = getVariableNamefromoperand(i->getOperand(0));
    //       op2 = getVariableNamefromoperand(i->getOperand(1));

    //       outFile << "-->" << getresultOperand(dyn_cast<Instruction>(i)) << "= "
    //               << valueTuple[getStringFromInstruction(dyn_cast<Instruction>(
    //                      i))][getresultOperand(dyn_cast<Instruction>(i))]
    //               << "\t";
    //       outs() << "-->" << getresultOperand(dyn_cast<Instruction>(i)) << "= "
    //               << valueTuple[getStringFromInstruction(dyn_cast<Instruction>(
    //                      i))][getresultOperand(dyn_cast<Instruction>(i))]
    //               << "\t";
          

    //       if (!isInteger(op1)) {
    //         op1 = valueTuple[getStringFromInstruction(dyn_cast<Instruction>(i))]
    //                         [op1];
    //         outFile << getVariableNamefromoperand(i->getOperand(0)) << " = "
    //                 << op1 << "\t";
    //         outs()<< getVariableNamefromoperand(i->getOperand(0)) << " = "
    //         << op1 << "\t";
    //       }
    //       if (!isInteger(op2)) {
    //         op2 = valueTuple[getStringFromInstruction(dyn_cast<Instruction>(i))]
    //                         [op2];
    //         outFile << getVariableNamefromoperand(i->getOperand(1)) << " = "
    //                 << op2;
    //         outs()<< getVariableNamefromoperand(i->getOperand(1)) << " = "
    //                 << op2;
    //       }

    //       pfel("\t\tBinary Instruction\n" << *i);
    //       // outs()<<"\t\tBinary Instruction\n" << *i<<"\n";
    //       // iterateME(dyn_cast<Instruction>(i));

    //       // pf("\t\ttesttt\t\t");
    //       // pfopel(i->getOperand(0));

    //       // pf(getVariableNamefromoperand(i->getOperand(0)) << "= ");
    //       // pf(getVariableNamefromoperand(i->getOperand(1)) << "= ");

    //       outFile << "\n";
    //       outs()<<"\n";
    //       break;
    //     }
    //     }

    //     // store i32 %5, i32* %6, align 4

    //     if (BranchInst *BI = dyn_cast<BranchInst>(i)) {
    //       // Do something with branch instruction BI
    //       // pfel(i->getOperand(0));
    //       // pfel("found you My Branch instruction \t\t");
    //       outFile << "\n";
    //       outs()<<"\n";
    //     }
    //   }
    //   // for (BasicBlock &BB : F) {
    //   //       for (Instruction &I : BB) {
    //   //         pfel(I);
    //   //           // if (StoreInst *SI = dyn_cast<StoreInst>(&I)) {
    //   //           //     // This instruction is a store instruction
    //   //           //     errs() << "Found store instruction: " << *SI <<
    //   // "\n";
    //   //           // }
    //   //       }
    //   //   }
    // }
    
    
    outFile.close();
    // outfile.close();
    return valueTuple;
  }

  void iterateCallsite(const std::map<std::string, std::map<std::string, std::string>>& callsite) {
    // Iterate over each entry in the outer map
    pfel("CALL SITES");
    for (const auto& outerPair : callsite) {
        const std::string& key1 = outerPair.first;
        const std::map<std::string, std::string>& innerMap = outerPair.second;
        
        // Print the key of the outer map
        pfel("Function called" << key1);

        // Iterate over each entry in the inner map
        for (const auto& innerPair : innerMap) {
            const std::string& key2 = innerPair.first;
            const std::string& value = innerPair.second;
            
            // Print the keys and value of the inner map
            pfel(" " << key2 << ": " << value);
        }
    }
}
void iterateValueTupleforFunction(const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& valueTupleforFunction) {
    // Iterate over each entry in the outer map
    for (const auto& outerPair : valueTupleforFunction) {
        const std::string& key1 = outerPair.first;
        const std::map<std::string, std::map<std::string, std::string>>& innerMap1 = outerPair.second;
        
        // Print the key of the outer map
        pfel("\t\t"<<key1<<"\n");

        // Iterate over each entry in the inner map1
        for (const auto& innerPair1 : innerMap1) {
            const std::string& key2 = innerPair1.first;
            const std::map<std::string, std::string>& innerMap2 = innerPair1.second;
            
            // Print the key of the inner map1
            pfel("\t"<<key2<<"\n" );

            
            //  printMapValues(valueTupleforFunction[key1][key2]);
            // Iterate over each entry in the inner map2
            for (const auto& innerPair2 : innerMap2) {
                const std::string& key3 = innerPair2.first;
                const std::string& value = innerPair2.second;
                
                // Print the keys and value of the inner map2
                pf("("<<key3 << ": " << value<<")");
                
            }pfel("");
        }
    }
}
void printFunctionInvocations(const std::map<std::string, int>& functionInvocations) {
    for (const auto& pair : functionInvocations) {
        pfel("Function: " << pair.first << ", Invocations: " << pair.second );
    }
}
void iterateFuncMap(const std::map<std::string, std::map<std::string, std::string>>& nestedMap) {
    for (const auto& outerPair : nestedMap) {
        std::cout << "Outer key: " << outerPair.first << std::endl;
        
        for (const auto& innerPair : outerPair.second) {
            std::cout << "  Inner key: " << innerPair.first << ", Inner value: " << innerPair.second << std::endl;
        }
    }
}

// map<string,map<string,string>>
// bool isAnyParameterConst(const map<string,string> map) {
//     for (int i = 0; i < map.size(); ++i) {
//         if (isInteger(map[i])) {
//             return 1; // Found an integer value
//         }
//     }
//     return 0; // No integer value found
// }

bool isAnyParameterConst(const std::map<std::string, std::string>& parameters) {
    for (const auto& pair : parameters) {
        // Attempt to convert the value to an integer
        char* end;
        std::strtol(pair.second.c_str(), &end, 10);

        // If conversion succeeded and the entire value was consumed,
        // then it is an integer
        if (*end == '\0') {
            return true;
        }
    }
    return false;
}
void updateMap(map<string, string>& des, map<string, string>& source) {
    for (auto& pair : des) {
        // Check if the key is not an integer
        if (pair.first.find_first_not_of("0123456789") != string::npos) {
            // Key is not an integer, update value from des map if present
            if (source.find(pair.first) != source.end()) {
                des[pair.first] = source[pair.first];
            }
        }
    }
}
// Function to transform variables into constants for binary operations
// void transformVariablesToConstants(Instruction *Inst, map<string, string> &VarMap) {
//     if (!Inst)
//         return;

//     // Check if the instruction is a binary operation
//     if (BinaryOperator *BinOp = dyn_cast<BinaryOperator>(Inst)) {
//         // Get the operands of the binary operation
//         Value *Op1 = BinOp->getOperand(0);
//         Value *Op2 = BinOp->getOperand(1);

//         // Process first operand
//         if (auto *Var1 = dyn_cast<Instruction>(Op1)) {
//             string VarName1 = Var1->getName().str();
//             if (VarMap.find(VarName1) != VarMap.end()) {
//                 string ConstValueStr1 = VarMap[VarName1];
//                 ConstantInt *ConstValue1 = ConstantInt::get(Var1->getType(), atoi(ConstValueStr1.c_str()));
//                 BinOp->setOperand(0, ConstValue1);
//             }
//         }

//         // Process second operand
//         if (auto *Var2 = dyn_cast<Instruction>(Op2)) {
//             string VarName2 = Var2->getName().str();
//             if (VarMap.find(VarName2) != VarMap.end()) {
//                 string ConstValueStr2 = VarMap[VarName2];
//                 ConstantInt *ConstValue2 = ConstantInt::get(Var2->getType(), atoi(ConstValueStr2.c_str()));
//                 BinOp->setOperand(1, ConstValue2);
//             }
//         }
//     }
// }

void constantPropagation(std::map<std::string, std::map<std::string, std::string>> valuetuple,Function &F,map<string,map<string,string>> callsite,
 LLVMContext &context)
{
  pfel("In constant prop");
  // LLVMContext context;
  
  map<Value*,Value*> todelete;
  for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
  {
    for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
    {
      Instruction *ist=dyn_cast<Instruction>(i);
      switch (ist->getOpcode()) {
        default:
          break;

        case Instruction::Alloca:{
          break;
        }
        case Instruction::Store: {
          pf("\t\tStore Instruction\n");
          if (StoreInst *Si = dyn_cast<StoreInst>(ist)) {
            // ist->replaceAllUsesWith(dyn_cast<ConstantInt>(99));
            ConstantInt* newValue = ConstantInt::get(Type::getInt32Ty(context), 100);


            pfel(" " << *ist << " ");

            unsigned numOperands = Si->getNumOperands();

            std::string variableName = Si->getPointerOperand()->getName().str();
            Value *storedValue = Si->getValueOperand();
            // storedValue->replaceAllUsesWith(newValue);
            todelete[storedValue]=newValue;

            // pfel("1st operand/variable name :");
            pf("-->");
            variableName = addmod(variableName);

            pf(variableName << " = "<<getStringfromVal(storedValue));
            // string destinationOpernad = getVariableNamefromoperand(storedValue);
            // pfel(destinationOpernad<<"?????????????????????????????");

            // val is int assign it to variable
            // if (isInteger(destinationOpernad)) {
            //   pfel("this is in store in instruction"<<variableName<<"="<<destinationOpernad);
            //   newMap[variableName] = destinationOpernad;

            // }else if(curMap.find(destinationOpernad)!=curMap.end())
            // {
            //   pfel(variableName<<">>"<<curMap[destinationOpernad]);
            //   newMap[variableName]=curMap[destinationOpernad];
            // }
            // else {
            //   newMap[variableName] =
            //       meetValue(curMap[variableName], destinationOpernad);
            //   // newMap[variableName] =
            //   // curMap[getVariableNamefromoperand(storedValue)];
            // }
          }
          break;
        }
      }
    }
  }
  for (auto& pair : todelete) {
        Value* key = pair.first;
        Value* value = pair.second;

        // Replace all uses of 'key' with 'value'
        key->replaceAllUsesWith(value);

        // Optionally, erase the instruction using the 'key'
        // if (Instruction* inst = dyn_cast<Instruction>(key)) {
        //     inst->eraseFromParent();
        // }
    }
}
void deleteInstructions(vector<Instruction*>& instructionsToDelete) {
    // Iterate through the vector of instructions to delete
    for (Instruction* Inst : instructionsToDelete) {
        // Check if the instruction is not null
        if (Inst) {
            // Remove the instruction from its parent basic block
            Inst->eraseFromParent();
        }
    }
}
void removeUnusedAllocaInstructions(Function &F) {
    for (auto &BB : F) {
        for (auto I = BB.begin(), E = BB.end(); I != E;) {
            AllocaInst *AI = dyn_cast<AllocaInst>(&*I++);
            if (!AI)
                continue;

            // Check if alloca instruction has any users
            if (AI->user_empty()) {
                // Remove the alloca instruction
                AI->eraseFromParent();
            }
        }
    }
}
void ChangeIR(std::map<std::string, std::map<std::string, std::string>> valueTuple,Function &F, LLVMContext &context)
{
  map<Value*,Value*> todelete;
  vector<Instruction*> legitDelete;
  for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
  {
    for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
    {
      Instruction *ist=dyn_cast<Instruction>(i);
      pfel(*ist<<"chala");
      
      printMapValues(valueTuple[getStringFromInstruction(ist)]);
      pfel("thamba");
      switch (ist->getOpcode()) {
        default:
          break;
        case Instruction::Load: {
          pf("\t\tTransformation Load\n");
          if (LoadInst *LI = dyn_cast<LoadInst>(ist)) {
            std::string s;

            raw_string_ostream os(s);
            LI->printAsOperand(os, false);
            
            
            // LI->getOperand(1);
            // LI->getOperand();
            os.flush();
            std::string instructionSubstr = os.str();
            // pf(*LI);
            std::string variableName = LI->getPointerOperand()->getName().str();
            variableName=addmod(variableName);
            unsigned numOperands = LI->getNumOperands();
            pfel("-->" << instructionSubstr << " = " << variableName);
            
            // string temp=valueTuple[getStringFromInstruction(ist)][variableName];
            // pfel("ll"<<getStringfromVal(LI));

            if(valueTuple[getStringFromInstruction(ist)].find(variableName)!=valueTuple[getStringFromInstruction(ist)].end() 
              && valueTuple[getStringFromInstruction(ist)][variableName]!="TOP"
              && valueTuple[getStringFromInstruction(ist)][variableName]!="BOTTOM"
            )
            {
              string temp=valueTuple[getStringFromInstruction(ist)][variableName];
              pfel("cool"<<temp);

              if (isInteger(temp))
              {
                pfel("haa");
                ConstantInt* newValue = ConstantInt::get(Type::getInt32Ty(context),stringToInt(temp) );
                todelete[LI]=newValue;
                
              }
              
            }
            
            
            // if(valueTuple[getStringFromInstruction(ist)].find(getStringfromVal(storedValue))!=valueTuple[getStringFromInstruction(ist)].end())
            // todelete[storedValue]=valueTuple[getStringFromInstruction(ist)][getStringfromVal(storedValue)];
            // todelete[LI->getOperand(0)]=

            // update from here
            // variable always has mode in load
            // instructionSubstr = addmod(instructionSubstr);

            // variableName=addmod(variableName);
            // string destinationOpernad = instructionSubstr;
            // if (isInteger(destinationOpernad)) {
            //   newMap[instructionSubstr] = destinationOpernad;

            // } else {
            //   pf("checkkkkkkkkk " << curMap[addmod(variableName)] << " "
            //                       << addmod(variableName));
            //   newMap[instructionSubstr] = curMap[addmod(variableName)];
            // }
          }
          break;
        }
        case Instruction::Store: {
          pf("\t\tTransformation Store\n");
          if (StoreInst *Si = dyn_cast<StoreInst>(ist)) {
            // ist->replaceAllUsesWith(dyn_cast<ConstantInt>(99));
            pfel(" " << *ist << " ");

            unsigned numOperands = Si->getNumOperands();

            std::string variableName = Si->getPointerOperand()->getName().str();
            Value *storedValue = Si->getValueOperand();
            variableName = addmod(variableName);
            // storedValue->replaceAllUsesWith(newValue);
            pfel("CC "<<variableName<<" = "<<getStringfromVal(storedValue));
            if(Si->user_empty())
            {
              pfel("babyyyy");
              legitDelete.push_back(Si);
            }
            else if(isInteger(getStringfromVal(storedValue)))
            {
              legitDelete.push_back(Si);

            }else
            {
              pfel(valueTuple[getStringFromInstruction(ist)][getStringfromVal(storedValue)]);
            if(valueTuple[getStringFromInstruction(ist)].find(getStringfromVal(storedValue))!=valueTuple[getStringFromInstruction(ist)].end() 
              && valueTuple[getStringFromInstruction(ist)][getStringfromVal(storedValue)]!="TOP"
              && valueTuple[getStringFromInstruction(ist)][getStringfromVal(storedValue)]!="BOTTOM"
            )
              {
                //have to check if the value is already constant
                //2nd condition for getting the constant value from the map 
                string temp=valueTuple[getStringFromInstruction(ist)][getStringfromVal(storedValue)];
                pfel("cool"<<temp);

                if (isInteger(temp))
                {
                  pfel("haa");
                  ConstantInt* newValue = ConstantInt::get(Type::getInt32Ty(context),stringToInt(temp) );
                  // todelete[storedValue]=newValue;
                  legitDelete.push_back(Si);
                  //write ways to
                  // todelete[Si->getPointerOperand()]=newValue;
                  
                }
                
              }

            }
            
          }
          break;
        }
        case Instruction::Call: {

          pfel("call Transformation\n"<<*ist);
          printMapValues(valueTuple[getStringFromInstruction(ist)]);
          
          if (CallInst *Si = dyn_cast<CallInst>(ist)) {
            Function *CalledFunc = Si->getCalledFunction();
            if(CalledFunc->getName().str()=="printf" )
            {
              pfel("Printf/scanf");
            }else if(CalledFunc->getName().str()=="__isoc99_scanf")
            {
              // newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";
            }else
            {
              // for (Argument &arg : CalledFunc->args()){
                
              // }
              for (Argument &arg : CalledFunc->args()) {
                // Print argument name and type
                string argumentStr=arg.getName().str();
                argumentStr=addmod(argumentStr);
                pfel("\n\nArgument name: " << argumentStr<<" ("<<getStringfromVal(Si->getOperand(arg.getArgNo()))<<")" );
                pfel(" retrieved value for "<<argumentStr);
                
                Value *callargs=Si->getArgOperand(arg.getArgNo());
                // pfel("somehting"<<callargs->getName());
                // pfel(getresultOperand(dyn_cast<Instruction>(callargs)));
                // callargs->printAsOperand(errs());
                
                if (isa<ConstantInt>(callargs)) {
                  ConstantInt *CI = cast<ConstantInt>(callargs);
                  errs() << "Parameter " << arg.getArgNo() << ": " << CI->getSExtValue() << "\n";
                  
                }
                
                else
                {
                  string actualParameter = getStringfromVal(Si->getOperand(arg.getArgNo()));
                  printMapValues(valueTuple[getStringFromInstruction(ist)]);
                  pfel("actual param"<<actualParameter<<" value from map"<<valueTuple[getStringFromInstruction(ist)][actualParameter]);
                  pfel("string instruction"<<getStringFromInstruction(dyn_cast<Instruction>(ist)));
                  // iterateFuncMap(valueTupleforFunction[CalledFunc->getName().str()]);
                  
                  // printMapValues(valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))]);
                  // string retrieved_val=valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))][getStringfromVal(Si->getOperand(arg.getArgNo()))];
                  string retrieved_val = valueTuple[getStringFromInstruction(ist)][actualParameter];
                  // string retrieved_val=curMap[getStringfromVal(Si->getOperand(arg.getArgNo()))];
                  pfel("Change IR intra const val to:("<<retrieved_val<<")");
                  ConstantInt* newValue = ConstantInt::get(Type::getInt32Ty(context),stringToInt(retrieved_val) );
                  // Si->setArgOperand(arg.getArgNo(), newValue);
                  // callsite[CalledFunc->getName().str()][argumentStr]=retrieved_val;
                  // callsite[to_string(insttoLine[dyn_cast<Instruction>(ist)])+"|"+CalledFunc->getName().str()][argumentStr]=retrieved_val;
                  // if(callsite.find(FuncName)==callsite.end())
                  // {
                  //   map<string,string> currParam;
                  //   currParam[argumentStr]=retrieved_val;
                  //   callsite[FuncName]=currParam;
                  // }else
                  // {
                  //   callsite[CalledFunc->getName().str()][argumentStr]=retrieved_val;
                  // }
                }
              }
            }
            
            // linetoInst[ii];
            // insttoLine[ii];
            // ii->eraseFromParent();
          }

          break;
        }
        case Instruction::Add:
        case Instruction::Sub:
        case Instruction::Mul:
        case Instruction::SDiv:
        case Instruction::UDiv:
        case Instruction::SRem:
        case Instruction::URem:
        case Instruction::Shl:
        case Instruction::LShr:
        case Instruction::AShr:
        case Instruction::And:
        case Instruction::Or:
        case Instruction::Xor:
        {
          pfel("\t\tBinary Transformation\n" << *ist);
          // iterateME(dyn_cast<Instruction>(i));
          string resultOperand, stringOp1, stringOp2;

          resultOperand = (getresultOperand(dyn_cast<Instruction>(ist)));
          stringOp1 = (getVariableNamefromoperand(ist->getOperand(0)));
          stringOp2 = (getVariableNamefromoperand(ist->getOperand(1)));

          string getit= valueTuple[getStringFromInstruction(ist)][resultOperand];

          pfel(resultOperand << "= resolved :"<<getit);
          if(isInteger(getit))
          {
            ConstantInt* newValue = ConstantInt::get(Type::getInt32Ty(context),stringToInt(getit) );
            todelete[ist]=newValue;

          }

          // std::string variableName = ist->getPointerOperand()->getName().str();
          // variableName=addmod(variableName);

          
          break;
          }

        
      }
      
      //
    }
  }
  for (auto& pair : todelete) {
        Value* key = pair.first;
        Value* value = pair.second;

        // Replace all uses of 'key' with 'value'
        key->replaceAllUsesWith(value);
        pfel("replace"<<getStringfromVal(key)<<" to "<<getStringfromVal(value));

        // Optionally, erase the instruction using the 'key'
        if (Instruction* inst = dyn_cast<Instruction>(key)) {
            inst->eraseFromParent();
        }
    }

    deleteInstructions(legitDelete);
    vector<Instruction *> allocadelet;

    for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
    {
      for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
      {
        Instruction *ist=dyn_cast<Instruction>(i);
        if( ist->getOpcode()== Instruction::Alloca) {
          pf("\t\tAlloca Instruction Transformation in \n");
            pf(*ist);
            std::string instructionSubstr = getresultOperand(dyn_cast<Instruction>(ist));
            if (AllocaInst *AI = dyn_cast<AllocaInst>(ist)) 

            if (AI->user_empty())
            {
              pfel("\nKAHI KHARA NAHI");
              // Remove the alloca instruction
              // AI->eraseFromParent();
              allocadelet.push_back(AI);
            }else
            {
              pfel("some");
              for (User *U : AI->users()) {
                      if (Instruction *UserInst = dyn_cast<Instruction>(U)) {
                          UserInst->print(errs());
                          errs() << "\n";
                      }
                  }
                  pfel("______");
            }
        }
      }
    }

    deleteInstructions(allocadelet);

  return;
}

//function name instruction map<key value>
void iterateModule(Module &M,map<string, map<string, map<string, string>>>& valueTupleforFunction)
{
  for (Function &F : M) 
  {
    string currFuncName=F.getName().str();
    pfel("\nFunction"<<currFuncName);

    for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
    {

      for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
      {
        Instruction *ist = &*i;
        pfel(*ist);
        // pfel(*dyn_cast<Instruction>(i));
        printMapValues(valueTupleforFunction[currFuncName][getStringFromInstruction(ist)]);
        pfel("");
      }
    }
  }

}


namespace {

  struct cons_eval:public ModulePass{
    static char ID;
    cons_eval() : ModulePass(ID) {}

    bool runOnModule (Module &M) override {
        pf("HII");
        LLVMContext &context = M.getContext();

        //key would be functionname:lineno;
        //we store map of parameter of each function inititally TOP
        
        map<string,vector<string>> mycallgraph;

        //each function and their keyvalue pairs or constants
        map<string,std::map<std::string, std::map<std::string, std::string>>> valueTupleforFunction;
        map<string,int> functionInvocations;
        map<int,Instruction *> linetoInst;
        map<string,Function *> nametoFunc;


        pfel("\n\n\n\n\n\n\n\n\n");
        // map<string,FunctionPtr> functionmaping;

        //we iterate the functions and basic  block to create
        //map function->vector<functionames> as call graph
        //we then while getting this function name get the constant prop
        // values and then update the parameters of the function calls
        //then iterate the function call graph and expand each one of  them


        for (Function &F : M) 
        {
          string currFuncName=F.getName().str();
          errs() << "\nFunction: " << currFuncName << "\n";
          nametoFunc[currFuncName]=&F;
          std::map<std::string, std::map<std::string, std::string>> curFuncMap;
          curFuncMap =kildalls(F);
          valueTupleforFunction[currFuncName]=curFuncMap;
          // printMapValues(curFuncMap);
          // iterateFuncMap(curFuncMap);

          // if(valueTupleforFunction.find(currFuncName)==valueTupleforFunction.end())
          // {
          //   valueTupleforFunction[currFuncName]=curFuncMap;
          // }else
          // {
          //   valueTupleforFunction[currFuncName]=curFuncMap;
          // }
          
          for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
          {
            pfel("innnn");
            int funcindex=0;

            for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
            {
              
              pfel(*i);
              if(i->getOpcode()==Instruction::Call)
              {
                
                pfel("CALL Instruction at"<<funcindex);
                if (CallInst *Si = dyn_cast<CallInst>(i)) {
                // iterateME(Si);

                Function *CalledFunc = Si->getCalledFunction();
                // CalledFunc->args()
                
                if (CalledFunc) {
                  if(functionInvocations.find(CalledFunc->getName().str())==functionInvocations.end())
                    functionInvocations[CalledFunc->getName().str()]=1;
                  else 
                    functionInvocations[CalledFunc->getName().str()]+=1;
                    
                  string FuncName = CalledFunc->getName().str();

                  FuncName=to_string(funcindex)+"|"+FuncName;
                  linetoInst[funcindex]=dyn_cast<Instruction>(i);
                  insttoLine[dyn_cast<Instruction>(i)]=funcindex;
                  string parentfunc = F.getName().str();
                  if(CalledFunc->getName().str()=="printf" || CalledFunc->getName().str()=="__isoc99_scanf")
                  {
                    pfel("Printf/scanf");
                  }else
                  {
                    pfel("parent caller"<<parentfunc);
                    if(mycallgraph.find(parentfunc)==mycallgraph.end())
                    {
                      pfel("adding to graphh new"<<FuncName);
                      vector<string > mycalls;
                      mycalls.push_back(FuncName);
                      mycallgraph[parentfunc]=mycalls;
                    }
                    else
                    {
                      pfel("appending to the graphh"<<FuncName);
                      mycallgraph[parentfunc].push_back(FuncName);
                    }

                  }
                  // outs()<<"hMM"<<FuncName<<"\n";
                  pfel("called fun is"<<FuncName);
                  if(CalledFunc->getName().str()=="printf" || CalledFunc->getName().str()=="__isoc99_scanf")
                  {
                    pfel("Printf/scanf");
                  }
                  //function is user defined 
                  else
                  {
                    for (Argument &arg : CalledFunc->args()) {
                      // Print argument name and type
                      string argumentStr=arg.getName().str();
                      argumentStr=addmod(argumentStr);
                      pfel("Argument name: " << argumentStr << ", Argument type: " << *arg.getType() );
                      pfel(getStringfromVal(Si->getOperand(arg.getArgNo()))<<"retrieved value for "<<argumentStr);
                        

                      
                      Value *callargs=Si->getArgOperand(arg.getArgNo());
                      // pfel("somehting"<<callargs->getName());
                      // pfel(getresultOperand(dyn_cast<Instruction>(callargs)));
                      // callargs->printAsOperand(errs());

                      //logic for passed constants as arguments
                      if (isa<ConstantInt>(callargs)) {
                        ConstantInt *CI = cast<ConstantInt>(callargs);
                        errs() << "Parameter " << arg.getArgNo() << ": " << CI->getSExtValue() << "\n";
                        if(callsite.find(FuncName)==callsite.end())
                        {
                          map<string,string> currParam;
                          currParam[argumentStr]=to_string(CI->getSExtValue());
                          callsite[FuncName]=currParam;
                        }else
                        {
                          callsite[FuncName][argumentStr]=to_string(CI->getSExtValue());
                        }
                        pfel("assigned valu is"<<callsite[FuncName][argumentStr]);
                      }else
                      {
                        pfel("string instruction"<<getStringFromInstruction(dyn_cast<Instruction>(i)));
                        // iterateFuncMap(valueTupleforFunction[CalledFunc->getName().str()]);
                        
                        // printMapValues(valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))]);
                        // string retrieved_val=valueTupleforFunction[CalledFunc->getName().str()][getStringFromInstruction(dyn_cast<Instruction>(i))][getStringfromVal(Si->getOperand(arg.getArgNo()))];
                        string retrieved_val=curFuncMap[getStringFromInstruction(dyn_cast<Instruction>(i))][getStringfromVal(Si->getOperand(arg.getArgNo()))];
                        pfel("RUN ON MODULE intra const val"<<retrieved_val);
                        if(callsite.find(FuncName)==callsite.end())
                        {
                          map<string,string> currParam;
                          currParam[argumentStr]=retrieved_val;
                          callsite[FuncName]=currParam;
                        }else
                        {
                          callsite[FuncName][argumentStr]=retrieved_val;
                        }
                      }


                      //new
                      // if(isInteger(argumentStr))
                      // {
                      //   pfel("isss instt"<<"#"+to_string(tempi));
                      //   if(callsite.find(FuncName)==callsite.end())
                      //   {
                      //     map<string,string> currParam;
                      //     currParam["#"+to_string(tempi)]=argumentStr;
                      //     callsite[FuncName]=currParam;
                      //   }else
                      //   callsite[FuncName]["#"+to_string(tempi)]=argumentStr;

                      // }else
                      // {
                      //   if(callsite.find(FuncName)==callsite.end())
                      //   {
                      //     map<string,string> currParam;
                      //     currParam[argumentStr]="TOP";
                      //     callsite[FuncName]=currParam;
                      //   }else
                      //   {
                      //     callsite[FuncName][argumentStr]="TOP";
                      //   }

                      // }
                      // tempi++;
                    }
                      pfel("something elseeeee");
                      // outs()<<getVariableNamefromoperand(Si->getOperand(1))<<"IS BOTTTTTTTTT";
                      // newMap[getVariableNamefromoperand(Si->getOperand(1))] = "BOTTOM";

                  }

                    // return FuncName.equals("printf") || FuncName.equals("scanf");
                }
                }
              }
              funcindex++;
              // transformVariablesToConstants(dyn_cast<Instruction>(i), callsite[FuncName]);

            }
            // pfel(*i);
          }
          
        }
        // map<string,vector<string>> mycallgraph;

        iterateCallGraph(mycallgraph);
        iterateCallsite(callsite);
        printFunctionInvocations(functionInvocations);
        
        // iterateValueTupleforFunction(valueTupleforFunction);
        errs().write_escaped(M.getName()) << '\n';
        
        std::queue<std::string> worklist;
        for(int i=0;i<mycallgraph["main"].size();i++)
        {
          worklist.push(mycallgraph["main"][i]);
          pfel("pushing in the queue"<<mycallgraph["main"][i]);
        }
        //iterate the queue 
        //1.take out a function
        //2.check if only function invocation exists
        //3.do the meet of all the function parameters if multiple invocation
        //4.go to the function body and propogate the constant values 
        //5. if this propogation affects another function call we update the parameter values
        // printQueue(worklist);
        map<string,bool> visited;
        for (const auto& pair : functionInvocations) 
        {
          visited[pair.first]=false;
        // pfel("Function: " << pair.first << ", Invocations: " << pair.second );
        }
        pfel("Queue is");
        printQueue(worklist);

        string curCall;
        // eg     3|foox 
        while(!worklist.empty())
        {
          curCall=worklist.front();
          visited[getValueAfterPipe(curCall)]=true;

          worklist.pop();
          //if the functino invocation is only once and even if one parameter is constant
          pfel(getValueAfterPipe(curCall)<<" invoc"<<functionInvocations[getValueAfterPipe(curCall)]);
          Function* curFunc=nametoFunc[getValueAfterPipe(curCall)];
          pfel(curCall<<":");
          printMapValues(callsite[curCall]);
          pfel("");
          pfel(getValueAfterPipe(curCall)<<":");
          printMapValues(callsite[getValueAfterPipe(curCall)]);
          
          std::map<std::string, std::map<std::string, std::string>> curFuncMapwithParam;
          
          
          curFuncMapwithParam= kildalls(*curFunc,curCall);
          // curFuncMapwithParam =kildalls(F);
          
          //we are assigning to the specific function i.e 3|bar
          // valueTupleforFunction[curCall]=curFuncMapwithParam;

          //we assign to generic eg bar
          valueTupleforFunction[getValueAfterPipe(curCall)]=curFuncMapwithParam;
          
          callsite[getValueAfterPipe(curCall)]=meet(callsite[curCall],callsite[getValueAfterPipe(curCall)]);
          
          printMapValues(callsite[getValueAfterPipe(curCall)]);
          pfel("___________________________________________");
          // if(functionInvocations[getValueAfterPipe(curCall)]==1)
          // {
            
          //   pfel(getValueAfterPipe(curCall)<<"has const param"<<isAnyParameterConst(callsite[curCall]));
          //   getValueAfterPipe(curCall);
            
          //   Function* visitFunc=nametoFunc[getValueAfterPipe(curCall)];
          //   constantPropagation(valueTupleforFunction[getValueAfterPipe(curCall)],*visitFunc,callsite,M.getContext());
          //   // visitFunc->eraseFromParent();
          //   // for (Function::iterator bb1 = visitFunc->begin(), e1 = visitFunc->end(); bb1 != e1; bb1++) 
          //   // {
          //   //   for (BasicBlock::iterator ii = bb1->begin(), ii2 = bb1->end(); ii != ii2;ii++)
          //   //   {
          //   //     pfel(">>"<<*ii);
                
          //   //     // transformVariablesToConstants(dyn_cast<Instruction>(ii), cur);

          //   //     if (CallInst *Si = dyn_cast<CallInst>(ii)) {
          //   //       Function *CalledFunc = Si->getCalledFunction();
          //   //       if(CalledFunc->getName().str()=="printf" || CalledFunc->getName().str()=="__isoc99_scanf")
          //   //       {
          //   //         pfel("Printf/scanf");
          //   //       }else
          //   //       {
          //   //         string keyfuncname=to_string(insttoLine[dyn_cast<Instruction>(ii)])+"|"+CalledFunc->getName().str();
          //   //         pfel("BRR"<<insttoLine[dyn_cast<Instruction>(ii)]<<" official"<<keyfuncname);
                    
          //   //         // pfel("BRRR"<<insttoLine[dyn_cast<Instruction>(ii)]<<" official"<<to_string(insttoLine[dyn_cast<Instruction>(ii)])+"|"+CalledFunc->getName().str());
          //   //         printMapValues(callsite[keyfuncname]);
          //   //         //update the callsite[keyfuncname] with the constants if the variable has constant values 
          //   //         // callsite[curCall] this values you have to update
                    
          //   //         //updateMap(callsite[keyfuncname],callsite[curCall]);
                    
          //   //         // pfel("new valssssss");
          //   //         // printMapValues(callsite[keyfuncname]);
          //   //       }
                  
          //   //       // linetoInst[ii];
          //   //       // insttoLine[ii];
          //   //       // ii->eraseFromParent();

                 
          //   //     }
                              
          //   //   }
          //   // }
          //   // //write a function to enter the function and transform the code and 
          //   // //also the callsites if req

          // }else{
          //   map<string,string>meetofcalls;
          //   meetofcalls=callsite[curCall];

          //   for (const auto& outerPair : callsite) {
          //     const std::string& key1 = outerPair.first;
          //     if(getValueAfterPipe(curCall)==getValueAfterPipe(outerPair.first))
          //     {
          //       meetofcalls=meet(callsite[curCall],meetofcalls);
          //       printMapValues(meetofcalls);
          //     }
          //     const std::map<std::string, std::string>& innerMap = outerPair.second;
              
          //     // Print the key of the outer map
          //     pfel("Function called" << key1);

              
          //   }

          //   //do meet of all the functions params and is any param const expand/go 
          //   //to the function for

          //   //iterate all callsite for this particular function get do its meet
          // }

          for(int i=0;i<mycallgraph[getValueAfterPipe(curCall)].size();i++)
          {
            worklist.push(mycallgraph[getValueAfterPipe(curCall)][i]);
            pfel("pushing in the queue from while"<<mycallgraph[getValueAfterPipe(curCall)][i]);
          }

        }

        for (Function &F : M) 
        {
          // transform()
          string currFuncName=F.getName().str();
          pfel("FINAL FUNC"<<currFuncName);
          ChangeIR(valueTupleforFunction[currFuncName],F,M.getContext());
          printMapValues(callsite[currFuncName]);
          pfel("");
        
        }
        // iterateValueTupleforFunction(valueTupleforFunction);
        // iterateModule(M,valueTupleforFunction);
        pfel("FINALLLLLL");
        for (Function &F : M) 
        {
          string currFuncName=F.getName().str();
          errs() << "\nFunction: " << currFuncName << "\n";
          
          for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) 
          {
            
            for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;i++)
            {
              pfel(*i);

            }
          }
        }


        return false;
      }
  };

  // struct ICP : public CallGraphSCCPass {
  //       static char ID;

  //       ICP() : CallGraphSCCPass(ID) {}

  //       // Override the runOnSCC method to iterate over functions based on call graph
  //       bool runOnSCC(CallGraphSCC &SCC) override {
  //           // Iterate over functions in the SCC
  //           for (CallGraphNode *CGN : SCC) {
  //             // CGN
  //               if (Function *F = CGN->getFunction()) {
  //                   // Print the name of each function
  //                   errs() << "Function: " << F->getName() << "\n";
  //               }
  //           }
  //           return false; // Indicate that the SCC was not modified
  //       }

  //       // We don't modify the module, so we return false
  //       bool doInitialization(CallGraph &CG) override {
  //           return false;
  //       }

  //       bool doFinalization(CallGraph &CG) override {
  //           return false;
  //       }
  //   };

// struct ICP : public FunctionPass {
//   static char ID;
//   ICP() : FunctionPass(ID) {}

  
//   bool runOnFunction(Function &F) override {
//     pf(F.getName() << '\n');
//     errs()<<"\n";
//     errs().write_escaped(F.getName()) << '\n';


//     kildalls(F);
    
//     // errs() << "Hello: ";
//     // errs().write_escaped(F.getName()) << '\n';
//     // for (Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++) {
//     //   for (BasicBlock::iterator i = bb->begin(), i2 = bb->end(); i != i2;
//     //         i++){
//     //       pfel(*i);
//     //     }
//     // }


//     return false;
//   }

// };

 // end of struct Hello

} // end of anonymous namespace

// char ICP::ID = 0;
// static RegisterPass<ICP> X("Interprop", "inter constant propogation Pass",
//                              false /* Only looks at CFG */,
//                              false /* Analysis Pass */);

char cons_eval::ID = 0;
static RegisterPass<cons_eval> X("cons_eval_given", "Constant Propagation Pass for Assignment",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

// namespace {
// struct cons_eval : public FunctionPass {
//   static char ID;
//   cons_eval() : FunctionPass(ID) {}

//   bool runOnFunction(Function &F) override {
//     // write your code here
//     return false;
//   }
// }; // end of struct alias_c
// }  // end of anonymous namespace

// char cons_eval::ID = 0;
// static RegisterPass<cons_eval> X("cons_eval_given", "Constant Propagation Pass for Assignment");
