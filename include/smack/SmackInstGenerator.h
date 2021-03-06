//
// Copyright (c) 2008 Zvonimir Rakamaric (zvonimir@cs.utah.edu)
// This file is distributed under the MIT License. See LICENSE for details.
//
#ifndef SMACKINSTVISITOR_H
#define SMACKINSTVISITOR_H

#include "smack/BoogieAst.h"
#include "smack/SmackRep.h"
#include "llvm/InstVisitor.h"
#include <set>

namespace smack {
  
class SmackInstGenerator : public llvm::InstVisitor<SmackInstGenerator> {

private:
  SmackRep& rep;
  ProcDecl& proc;
  Block* currBlock;
  map<const llvm::BasicBlock*, Block*>& blockMap;
  int blockNum;
  int varNum;

  void generatePhiAssigns(llvm::TerminatorInst& i);
  void generateGotoStmts(llvm::Instruction& i,
                         vector<pair<const Expr*, string> > target);
  void processInstruction(llvm::Instruction& i);
  void nameInstruction(llvm::Instruction& i);
  void annotate(llvm::Instruction& i, Block* b);

public:
  SmackInstGenerator(SmackRep& r, ProcDecl& p,
                     map<const llvm::BasicBlock*, Block*>& bm)
    : rep(r), proc(p),
      blockMap(bm), blockNum(0), varNum(0) {}

  Block* createBlock();
  void setCurrBlock(Block* b) {
    currBlock = b;
  }
  Block* getCurrBlock() {
    return currBlock;
  }

  string createVar();

  void visitInstruction(llvm::Instruction& i);

  void visitReturnInst(llvm::ReturnInst& i);
  void visitBranchInst(llvm::BranchInst& i);
  void visitSwitchInst(llvm::SwitchInst& i);
  // TODO implement indirectbr
  // TODO implement invoke
  // TODO implement resume
  void visitUnreachableInst(llvm::UnreachableInst& i);
  
  void visitBinaryOperator(llvm::BinaryOperator& i);

  // TODO implement extractelement
  // TODO implement insertelement
  // TODO implement shufflevector

  // TODO implement extractvalue
  // TODO implement insertvalue
  
  void visitAllocaInst(llvm::AllocaInst& i);
  void visitLoadInst(llvm::LoadInst& i);
  void visitStoreInst(llvm::StoreInst& i);
  // TODO implement fence
  void visitAtomicCmpXchgInst(llvm::AtomicCmpXchgInst& i);
  void visitAtomicRMWInst(llvm::AtomicRMWInst& i);
  void visitGetElementPtrInst(llvm::GetElementPtrInst& i);

  void visitTruncInst(llvm::TruncInst& i);
  void visitZExtInst(llvm::ZExtInst& i);
  void visitSExtInst(llvm::SExtInst& i);
  void visitFPTruncInst(llvm::FPTruncInst& i);
  void visitFPExtInst(llvm::FPExtInst& i);
  void visitFPToUIInst(llvm::FPToUIInst& i);
  void visitFPToSIInst(llvm::FPToSIInst& i);
  void visitUIToFPInst(llvm::UIToFPInst& i);
  void visitSIToFPInst(llvm::SIToFPInst& i);
  void visitPtrToIntInst(llvm::PtrToIntInst& i);
  void visitIntToPtrInst(llvm::IntToPtrInst& i);
  void visitBitCastInst(llvm::BitCastInst& i);
  // TODO implement addrspacecast

  void visitICmpInst(llvm::ICmpInst& i);
  void visitFCmpInst(llvm::FCmpInst& i);
  void visitPHINode(llvm::PHINode& i);
  void visitSelectInst(llvm::SelectInst& i);
  void visitCallInst(llvm::CallInst& i);
  // TODO implement va_arg
  // TODO landingpad
  
  void visitMemCpyInst(llvm::MemCpyInst& i);
};
}

#endif // SMACKINSTVISITOR_H

