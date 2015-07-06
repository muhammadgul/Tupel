#ifndef TREEHELPER_H
#define TREEHELPER_H

/** Class to handle ROOT tree leaves.
 */

#include "TTree.h"
#include <memory>

/** Helper class for TTree. This helper takes care of resetting
 * the variable storage after a tree fill. The values of the simple
 * type variable are set to 0 and the vectors are empty.
 * Supported simple types: bool, int, float, double
 * Supported vector types: std::vector of above simple types
 */
class TreeHelper{
public:
  TreeHelper(TTree* tree): tree_(tree){
  }

  /** Add a branch of one the supported vector types
   * @param branchName name of the new branch
   * @param v auto pointer to store the variable attached to the branch
   */
  template<typename T>
  void addBranch(const char* branchName, std::auto_ptr<std::vector<T> >& v){
    std::vector<T>* p = new std::vector<T>;
    v = std::auto_ptr<std::vector<T> >(p);
    addVar(p);
    tree_->Branch(branchName, p);
  }

  /** Add a branch of one the supported simple types
   * @param branchName name of the new branch
   * @param v auto pointer to store the variable attached to the branch
   */
  template<typename T>
  void addBranch(const char* branchName, std::auto_ptr<T>& v){
    v = std::auto_ptr<T> (new T);
    *v = 0;
    tree_->Branch(branchName, v.get());
  }

  /** Reset the variables attached to the tree branches
   */
  void clear();

  /** Fill tree and reset variables attached to the tree branches
   */
  void fill(){
    tree_->Fill();
    clear();
  }

private:
  
  //Clear std::vector
  //@param v list of the pointers to thevectors to clear provided as a std::vector.
  template<typename T>
  void clear(std::vector<std::vector<T>*>& v){
    for(typename std::vector<std::vector<T>*>::iterator it = v.begin(); it != v.end(); ++it){
      (*it)->clear();
    }
  }
  
  template<typename T>
  void clear(std::vector<T*>& v){
    for(typename std::vector<T*>::iterator it = v.begin(); it != v.end(); ++it){
      **it = 0;
    }
  }
  
  //add an element to the list of variables
  //to clear after a tree fill
  void addVar(std::vector<int>* v){
    intVectorList_.push_back(v);
  }
  void addVar(std::vector<unsigned>* v){
    unsignedVectorList_.push_back(v);
  }
  void addVar(std::vector<float>* v){
    floatVectorList_.push_back(v);
  }
  void addVar(std::vector<double>* v){
    doubleVectorList_.push_back(v);
  }
  void addVar(std::vector<bool>* v){
    boolVectorList_.push_back(v);
  }
  void addVar(int* a){
    intList_.push_back(a);
  }
  void addVar(unsigned* a){
    unsignedList_.push_back(a);
  }
  void addVar(float* a){
    floatList_.push_back(a);
  }
  void addVar(double* a){
    doubleList_.push_back(a);
  }

private:
  std::vector<int*> intList_;
  std::vector<unsigned*> unsignedList_;
  std::vector<float*> floatList_;
  std::vector<double*> doubleList_;
  std::vector<std::vector<int>*> intVectorList_;
  std::vector<std::vector<unsigned>*> unsignedVectorList_;
  std::vector<std::vector<float>*> floatVectorList_;
  std::vector<std::vector<double>*> doubleVectorList_;
  std::vector<std::vector<bool>*> boolVectorList_;

  TTree* tree_;
};
  

#endif //TREEHELPER_H not defined
