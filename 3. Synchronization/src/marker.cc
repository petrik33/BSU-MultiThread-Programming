#include "../includes/marker.h"

#include "../includes/utils.h"

namespace data_marker {

Marker::Marker(int index) : index_(index), marked_elements_() {
    srand(index);
}

void Marker::MarkTargetElement() {
    data_.get()->at(mark_target_) = index_;
    marked_elements_.push_back(mark_target_);
}

void Marker::FindMarkTarget() {
    mark_target_ = utils::GetRandomNumber(0, data_.get()->size());
}

bool Marker::TargetIsMarkable() {
    return data_.get()->at(mark_target_) == 0;
}

void Marker::UnmarkElements() {
    for (auto& idx : marked_elements_) {
        data_.get()->at(idx) = 0;
    }
}

void Marker::PrintIndex(std::ostream& stream) const {
    stream << "Thread number " << index_ << std::endl;
}

void Marker::PrintMarkedElementsNumber(std::ostream& stream) const {
    stream << "Elements marked: " << marked_elements_.size() << std::endl;
}

void Marker::PrintUnmarkableElement(std::ostream& stream) const {
    stream << "Unable to mark element " << mark_target_ + 1 << std::endl;
}

}  // namespace data_marker