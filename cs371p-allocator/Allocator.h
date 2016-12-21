#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument

// ---------
// Allocator
// ---------

template <typename T, std::size_t N>
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type;

        typedef std::size_t       size_type;
        typedef std::ptrdiff_t    difference_type;

        typedef       value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef       value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) {
            return true;}                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

    private:
        // ----
        // data
        // ----

        char a[N];

        /**
        * return value of an address location
        */
        int get_val(char* ptr) {
            return *reinterpret_cast<const int*> (ptr);}

        /**
        * set value of an address location
        */
        void set_val(char* ptr, int a) {
            int* set_ptr = (int*) (ptr);
            *set_ptr = a;}

        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time
         * check if sentinel is valid
         */
         FRIEND_TEST(TestAllocator4, valid_1);
         FRIEND_TEST(TestAllocator4, valid_2);
         FRIEND_TEST(TestAllocator4, valid_3);
         FRIEND_TEST(TestAllocator5, Allocator_1);
         FRIEND_TEST(TestAllocator5, Allocator_2);
         FRIEND_TEST(TestAllocator5, Allocator_3);
         bool valid () const {
             // <your code>
             assert (N > (2 * sizeof(int)));

             int* ptr = (int*) a;
             while (ptr < (int*) (&a[N - sizeof(int)])) {
                 int size = abs(*ptr);
                 ptr = (int*) ((char*) ptr + size + sizeof(int));
                 if (abs(*ptr) != size)
                     return false;
                 ptr = (int*) ((char*) ptr + sizeof(int));
             }
             return true;
         }

        /**
         * O(1) in space
         * O(1) in time
         * return a reference at the location of the given index
         * https://code.google.com/p/googletest/wiki/AdvancedGuide#Private_Class_Members
         */
        FRIEND_TEST(TestAllocator2, index);
        FRIEND_TEST(TestAllocator6, allocate_1);
        FRIEND_TEST(TestAllocator6, allocate_2);
        FRIEND_TEST(TestAllocator6, allocate_3);
        FRIEND_TEST(TestAllocator6, allocate_4);
        FRIEND_TEST(TestAllocator6, allocate_5);
        FRIEND_TEST(TestAllocator7, deallocate_1);
        FRIEND_TEST(TestAllocator7, deallocate_2);
        FRIEND_TEST(TestAllocator7, deallocate_3);
        FRIEND_TEST(TestAllocator7, deallocate_4);
        FRIEND_TEST(TestAllocator7, deallocate_5);
        int& operator [] (int i) {
            return *reinterpret_cast<int*>(&a[i]);}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
         */
        Allocator () {
            // (*this)[0] = 0; // replace
            // <your code>
            if (N < sizeof(T) + (2 * sizeof(int)))
                throw std::bad_alloc();

            int* ptr = (int*) a;
            *ptr = N - (2 * sizeof(int));
            ptr = (int*) (&a[N - sizeof(int)]);
            *ptr = N - (2 * sizeof(int));
        }

        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         * throw a bad_alloc exception, if n is invalid
         */
        pointer allocate (size_type n) {
            // <your code>
            if (n <= 0 || n > (N - 2*sizeof(int))/sizeof(T)) throw std::bad_alloc();
            // if (n > (N - 2*sizeof(int))/sizeof(T)) throw std::bad_alloc();

            int n_size = n * sizeof(T);
            char* ptr = a;

            //search for first fit block
            while (ptr < &a[N - sizeof(int)]) {
                int sentinel_val = get_val(ptr);
                //chech if there is a fit block
                if (sentinel_val >= n_size + (2 * sizeof(int))) {
                    //if free space left is not enough for another free block
                    //allocate whole block
                    if (sentinel_val < n_size + sizeof(T) + (2 * sizeof(int))) {
                        int size = get_val(ptr);
                        set_val(ptr, 0 - size);
                        set_val(ptr + size + sizeof(int), 0 - size);
                        assert(valid());
                        return ((pointer) (ptr + sizeof(int)));

                    //if free space left is enough for another free block
                    //form a new block
                    } else {
                        int free_space = sentinel_val - n_size - (2 * sizeof(int));
                        char* _e = ptr + sentinel_val + sizeof(int);

                        //allocate block
                        set_val(ptr, -n_size);
                        ptr = ptr + n_size + sizeof(int);
                        set_val(ptr, -n_size);

                        //set the free space left
                        set_val(_e, free_space);
                        _e = _e - free_space - sizeof(int);
                        set_val(_e, free_space);

                        // assert(valid());
                        return (pointer) (ptr - n_size);
                    }


                //block is not fit, move to the next one
                } else
                    ptr += (abs)(*ptr) + (2 * sizeof(int));}

            assert(valid());
            return 0;
        }             // replace!

        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time
         */
        void construct (pointer p, const_reference v) {
            new (p) T(v);                               // this is correct and exempt
            assert(valid());}                           // from the prohibition of new

            // ---------
            // coalesce
            // ---------

            /**
            * concatenate 2 free blocks together
            */
        void coalesce_blocks(char* left, char* right) {
            assert(get_val(left) > 0);
            assert(get_val(right) > 0);

            char* ptr = left;
            int new_size = get_val(left) + get_val(right) + 2 * sizeof(int);

            ptr = ptr - get_val(left) - sizeof(int);
            set_val(ptr, new_size);

            ptr = ptr + get_val(right) + sizeof(int);
            set_val(ptr, new_size);
        }

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * after deallocation adjacent free blocks must be coalesced
         * throw an invalid_argument exception, if p is invalid
         * deallocate used blocks and coalesce free blocks
         */
        void deallocate (pointer p, size_type) {
            // <your code>
            if (p == nullptr) throw std::invalid_argument("Argument is null");
            //get start position
            char* _b = (char*)(p) - sizeof(int);
            set_val(_b, 0 - get_val(_b));

            //get end position
            char* _e = (char*)(p) + get_val(_b);
            set_val(_e, 0 - get_val(_e));

            //concatenate start to the left
            if (_b > &a[4]) {
                char* left = _b - sizeof(int);
                if (get_val(left) > 0)
                    coalesce_blocks(left, _b);}

            //concatenate end to the right
            if (_e < &a[N - 3]) {
                char* right = _e + sizeof(int);
                if (get_val(right) > 0)
                    coalesce_blocks(_e, right);}
            // assert(valid());
        }

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         */
        void destroy (pointer p) {
            p->~T();               // this is correct
            assert(valid());}

        /**
         * O(1) in space
         * O(1) in time
         * return a const reference at the location of the given index
         */
        const int& operator [] (int i) const {
            return *reinterpret_cast<const int*>(&a[i]);}};


#endif // Allocator_h
