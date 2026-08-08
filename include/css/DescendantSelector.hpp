#include "css/TagSelector.hpp"

struct DescendantSelector : public Selector {
    std::unique_ptr<Selector> ancestor;
    std::unique_ptr<Selector> descendant;
    
    bool matches(Token*) const override;

    DescendantSelector(std::unique_ptr<Selector> ancestor,
                   std::unique_ptr<Selector> descendant)
        : ancestor(std::move(ancestor)), descendant(std::move(descendant)) {
            priority = this->ancestor->priority + this->descendant->priority;
        }
};