#include <iostream>
#include <vector>
#include <algorithm>

namespace ariel {
    class MagicalContainer {
    public:
        MagicalContainer();
        class AscendingIterator {
        public:
            AscendingIterator(const MagicalContainer& mc);
            AscendingIterator begin();
            AscendingIterator end();
            AscendingIterator& operator++();
            int operator*();
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
        };

        class SideCrossIterator {
        public:
            SideCrossIterator(const MagicalContainer& mc);
            SideCrossIterator begin();
            SideCrossIterator end();
            SideCrossIterator& operator++();
            int operator*();
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
        };

        class PrimeIterator {
        public:
            PrimeIterator(const MagicalContainer& mc);
            PrimeIterator begin();
            PrimeIterator end();
            PrimeIterator& operator++();
            int operator*();
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
        };

        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
    
    private:
        std::vector<int> elements;
    };
}
