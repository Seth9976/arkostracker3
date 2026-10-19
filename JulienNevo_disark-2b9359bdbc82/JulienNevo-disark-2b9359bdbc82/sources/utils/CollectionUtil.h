#pragma once

#include <algorithm>

namespace disark
{

/** Some utility methods for collections. */
class CollectionUtil
{
public:
    /** Prevents instantiation. */
    CollectionUtil() = delete;

    /**
     * Shrinks the given collection, if it is bigger than the given size.
     * @tparam COLLECTION the collection type.
     * @param collection the collection to shrink.
     * @param maximumSize the maximum the collection must have.
     */
    template<typename COLLECTION>
    static void shrinkIfBigger(COLLECTION& collection, size_t maximumSize) noexcept
    {
        if (collection.size() > maximumSize) {
            collection.resize(maximumSize);
        }
    }

    /**
     * Removes items from the given Collection IF THEY FIT the given predicate.
     * @tparam COLLECTION the collection type.
     * @tparam PREDICATE the predicate type.
     * @param collection the collection.
     * @param removeIf the predicate that, if true, will remove the items.
     */
    template<typename COLLECTION, typename PREDICATE>
    static void removeIfAndResize(COLLECTION& collection, const PREDICATE& removeIf) noexcept
    {
        // Removes the ones that fit the predicate.
        auto iterator = std::remove_if(collection.begin(), collection.end(), removeIf);
        // Removes what remains. C++...
        collection.erase(iterator, collection.end());
    }

    template<typename MAP, typename KEY>
    static std::vector<KEY> mapToVector(const MAP& map) noexcept
    {
        std::vector<KEY> outputVector;
        for (auto iterator = map.cbegin(); iterator != map.cend(); ++iterator) {
            outputVector.emplace_back(iterator->first);
        }

        return outputVector;
    }

    /**
     * Finds an item in the given collection, returning its index.
     * @tparam COLLECTION the collection type.
     * @tparam ITEM the item type.
     * @param collection the collection to browse.
     * @param itemToFind the item to find.
     * @return the index, or -1 if the item could not be found.
     */
    template<typename COLLECTION, typename ITEM>
    static int findItemAndGetIndex(const COLLECTION& collection, const ITEM& itemToFind) noexcept
    {
        auto index = 0;
        // Browses the collection. Have to do it "manually" in order to get the index.
        for (auto iterator = collection.cbegin(); iterator != collection.cend(); ++iterator, ++index) {
            if (*iterator == itemToFind) {
                // Founded the item! We can leave.
                return index;
            }
        }

        // Not found!
        return -1;
    }
};

}    // namespace disark
