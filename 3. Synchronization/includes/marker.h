#ifndef INCLUDES_MARKER_H_
#define INCLUDES_MARKER_H_

#include <iostream>
#include <vector>

namespace marker {

class Marker {
   public:
    explicit Marker(int index);
    void MarkElement(std::vector<int>& data, int element_index);
    void UnmarkElements(std::vector<int>& data);
    static int FindMarkTarget(std::vector<int>& data);
    static bool ElementIsMarkable(std::vector<int>& data, int element_index);
    void PrintIndex(std::ostream& stream) const;
    void PrintMarkedElementsNumber(std::ostream& stream) const;
    void PrintUnmarkableElement(std::ostream& stream, int element_index) const;

   private:
    std::vector<int> marked_elements_;  // indexes
    int index_;
};

}  // namespace marker

#endif /* INCLUDES_MARKER_H_ */
