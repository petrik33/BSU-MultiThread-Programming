#ifndef INCLUDES_MARKER_H_
#define INCLUDES_MARKER_H_

#include "./types.h"

namespace data_marker {

class Marker {
   public:
    explicit Marker(int index, shared_ptr<mark_data> data);
    void MarkTargetElement();
    void UnmarkElements();
    void FindMarkTarget();
    bool TargetIsMarkable();
    void PrintFinishedMarking(ostream& stream) const;
    void PrintIndex(ostream& stream) const;
    void PrintMarkedElementsNumber(ostream& stream) const;
    void PrintUnmarkableElement(ostream& stream) const;

   private:
    shared_ptr<mark_data> data_;
    vector<int> marked_elements_;  // indexes
    int index_;
    int mark_target_;
};

}  // namespace data_marker

#endif /* INCLUDES_MARKER_H_ */
