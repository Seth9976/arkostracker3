#pragma once

#include <map>
#include <vector>

namespace disark
{

class MapUtil
{
public:

    /**
     * Adds a value to a map of lists.
     * @tparam KEY the type of the keys.
     * @tparam VALUE the type of the values.
     * @param mapToList the collection to fill.
     * @param key the key to add/update.
     * @param value the item to add.
     */
    template<typename KEY, typename VALUE>
    static void addValueToMapOfListOfValues(std::map<KEY, std::vector<VALUE>>& mapToList, const KEY& key, const VALUE& value) noexcept
    {
        // Does the entry exist?
        auto iterator = mapToList.find(key);
        if (iterator == mapToList.cend()) {
            // Creates a new list, it doesn't exist yet.
            std::vector<VALUE> list;
            list.emplace_back(value);

            mapToList.insert(std::make_pair(key, list));
        } else {
            // The list already exist. Simply append the value.
            iterator->second.emplace_back(value);
        }
    }
};

}    // namespace disark
