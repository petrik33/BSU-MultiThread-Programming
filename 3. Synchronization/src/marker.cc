#include "../includes/marker.h"

namespace data_marker {

Marker::Marker(int index, shared_ptr<mark_data> data) : data_(data), marked_elements_(), index_(index) {
    srand(index);
}

void Marker::MarkTargetElement() {
    data_.get()->at(mark_target_) = index_ + 1;
    marked_elements_.push_back(mark_target_);
}

void Marker::FindMarkTarget() {
    int max_index = data_.get()->size();
    mark_target_ = GetRandomNumber(0, max_index);
}

bool Marker::TargetIsMarkable() {
    return data_.get()->at(mark_target_) == 0;
}

void Marker::PrintFinishedMarking(ostream& stream) const {
    PrintIndex(stream);
    PrintMarkedElementsNumber(stream);
    PrintUnmarkableElement(stream);
}

void Marker::UnmarkElements() {
    for (auto& idx : marked_elements_) {
        data_.get()->at(idx) = 0;
    }
}

void Marker::PrintIndex(std::ostream& stream) const {
    stream << "Thread number " << index_ + 1 << std::endl;
}

void Marker::PrintMarkedElementsNumber(std::ostream& stream) const {
    stream << "Elements marked: " << marked_elements_.size() << std::endl;
}

void Marker::PrintUnmarkableElement(std::ostream& stream) const {
    stream << "Unable to mark element " << mark_target_ + 1 << std::endl;
}

}  // namespace data_marker