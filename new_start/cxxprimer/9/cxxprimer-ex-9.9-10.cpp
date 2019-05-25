/*
 * Ex 9.9
 *     begin() returns iterator while cbegin() returns const
 *     iterator.
 *
 * Ex 9.10
 *     vector<int> v1;
 *     const vector<int> v2;
 *     auto it1 = v1.begin(), -> vector<int>::iterator
 *          it2 = v2.begin(), -> vector<int>::const_iterator
 *          it3 = v1.cbegin(), -> vector<int>::const_iterator
 *          it4 = v2.cbegin(); -> vector<int>::const_iterator
 */
