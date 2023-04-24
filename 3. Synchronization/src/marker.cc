#include "../includes/marker.h"

#include "../includes/utils.h"

namespace marker {

Marker::Marker(int index) : index_(index), marked_elements_() {
    srand(index);
}

void Marker::MarkElement(std::vector<int>& data, int element_index) {
    data[element_index] = index_;
    marked_elements_.push_back(element_index);
}

int Marker::FindMarkTarget(std::vector<int>& data) {
    return utils::GetRandomNumber(0, data.size());
}

bool Marker::ElementIsMarkable(std::vector<int>& data, int element_index) {
    return data[element_index] == 0;
}

void Marker::UnmarkElements(std::vector<int>& data) {
    for (auto& idx : marked_elements_) {
        data[idx] = 0;
    }
}

void Marker::PrintIndex(std::ostream& stream) const {
    stream << "Thread number " << index_ << std::endl;
}

void Marker::PrintMarkedElementsNumber(std::ostream& stream) const {
    stream << "Elements marked: " << marked_elements_.size() << std::endl;
}

void Marker::PrintUnmarkableElement(std::ostream& stream, int element_index) const {
    stream << "Unable to mark element " << element_index + 1 << std::endl;
}

}  // namespace marker