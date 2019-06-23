/** @DESCRIPTION
 *  Why std::shared_ptr do not have the member `release`?
 */

// Since the `release` in unique_ptr is used to transfer ownership between
// unique_ptrs, it simply unbind the data from this unique_ptr and return
// the data pointer to initialize another unique_ptr. While in share_ptr,
// it is meaningless to do so, since if I am a shared_ptr, my brothers will
// automatically manage my resource if i dead.

