#ifndef INCLUDE_ARRAY_THREAD_H_
#define INCLUDE_ARRAY_THREAD_H_

namespace array_thread {
class IArrayThreadProps {
   public:
    IArrayThreadProps(int* array, int size);
    int* array() const;
    int size() const;

   private:
    int* array_;
    int size_;
};
}  // namespace array_thread

#endif /* INCLUDE_ARRAY_THREAD_H_ */
