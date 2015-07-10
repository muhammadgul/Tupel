#include "TreeHelper.h"
//Clear event vectors
void TreeHelper::clear(){
  clear(intVectorList_);
  clear(unsignedVectorList_);
  clear(floatVectorList_);
  clear(doubleVectorList_);
  clear(boolVectorList_);
  clear(intList_);
  clear(unsignedList_);
  clear(floatList_);
  clear(doubleList_);
}

//TODO object created in below function should be deleted in the desttructor
void TreeHelper::defineBit(const char* branchName, int bit, const char* bitDescription){
  if(!bitFieldTree_) return;
  if(bit < 0 || bit > 31) return;

  TBranch* br = bitFieldTree_->FindBranch(branchName);

  char *desc_ = new char[strlen(bitDescription)+1];
  strcpy(desc_, bitDescription);

  if(!br){
    std::vector<char*>* vec = new std::vector<char*>(32);
    for(unsigned i = 0; i < vec->size(); ++i){
      if(i==(unsigned)bit && bitDescription){
	(*vec)[i] = desc_;
      } else{
	(*vec)[i] = 0;
      }
    }
    bitFieldTree_->Branch(branchName, vec);
  } else{
    std::vector<char*>* vec = (std::vector<char*>*) br->GetAddress();
    if((*vec)[bit]){
      delete[] (*vec)[bit];
      (*vec)[bit] = desc_;
    }
  }
}
