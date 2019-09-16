#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/User.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Pass.h>
#include <fstream>
#include <llvm/Analysis/CFG.h>
#include <stdio.h>
#include <map>
using namespace llvm;

namespace {
	struct CFGPass : public FunctionPass {
		static char ID;
		std::error_code error;
		std::string str;
		//StringMap<int> basicblockMap;
		std::map<BasicBlock*, int> basicBlockMap;
		int bbCount;  //Block的编号
		CFGPass() : FunctionPass(ID){
			bbCount = 0;
		}

		bool runOnFunction(Function &F) override {
			raw_string_ostream rso(str);
			StringRef name(F.getName().str() + ".dot");
			
			enum sys::fs::OpenFlags F_None;
			raw_fd_ostream file(name, error, F_None);
			//std::ofstream os;
			//os.open(name.str() + ".dot");
			//if (!os.is_open()){
			//	errs() << "Could not open the " << name << "file\n";
			//	return false;
			//}
			file << "digraph \"CFG for'" + F.getName() + "\' function\" {\n";
			for (Function::iterator B_iter = F.begin(); B_iter != F.end(); ++B_iter){
				BasicBlock* curBB = &*B_iter;
				std::string name = curBB->getName().str();
				int fromCountNum;
				int toCountNum;
				if (basicBlockMap.find(curBB) != basicBlockMap.end())
				{
					fromCountNum = basicBlockMap[curBB];
				}
				else
				{
					fromCountNum = bbCount;
					basicBlockMap[curBB] = bbCount++;
				}

				file << "\tBB" << fromCountNum << " [shape=record, label=\"{";
				file << "BB" << fromCountNum << ":\\l\\l";
				for (BasicBlock::iterator I_iter = curBB->begin(); I_iter != curBB->end(); ++I_iter) {
					//printInstruction(&*I_iter, os);
					file << *I_iter << "\\l\n";
				}
				file << "}\"];\n";
				for (BasicBlock *SuccBB : successors(curBB)){
					if (basicBlockMap.find(SuccBB) != basicBlockMap.end())
					{
						toCountNum = basicBlockMap[SuccBB];
					}
					else
					{
						toCountNum = bbCount;
						basicBlockMap[SuccBB] = bbCount++;
					}

					file << "\tBB" << fromCountNum<< "-> BB"
						<< toCountNum << ";\n";
				}
			}
			file << "}\n";
			file.close();
			return false;
		}
		//void printInstruction(Instruction *inst, std::ofstream os) {

	//}
	};
}
char CFGPass::ID = 0;
static RegisterPass<CFGPass> X("CFG", "CFG Pass Analyse",
	false, false
);

