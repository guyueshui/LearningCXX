/*
 * Ex 9.11
 *   - vector<int> a = {1,2,3,4,5}; -> {1,2,3,4,5}
 *   - vector<int> b(a); -> {1,2,3,4,5}
 *   - vector<int> b = a; -> {1,2,3,4,5}
 *   - vector<int> b(a.begin(), a.end()); -> {1,2,3,4,5}
 *   - vector<int> c(5,0); -> {0,0,0,0,0}
 *   - vector<int> d(5); -> {0,0,0,0,0}
 *
 * Ex 9.12
 *  - copiable container: container type and element type
 *    perfect match.
 *  - iterator range: the elements from the target and source
 *    can be transformed implicitly.
 */
