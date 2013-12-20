/**
 * @file ManagerView.cpp
 * @date march 25 2013.
 * @author Tom Hadlaw
 * @brief Namespace for binary heap queue object.
 */
#include <iostream>
#include <cstdlib>
using namespace std;

#define HEAP_SIZE 257 //defines maximum heap size

namespace BinHeap
{
    /*
     * Used as a comparator for object T with a defined 
     * equality operator. used for constructing Min Binary Heap
     */
    template <typename T> class MinHeapSorter
    {
        public:
            /*
             * Returns true if a is before b, false otherwise (for minheap)
             */
            bool before(const T& a,const T& b) const
            {
                if (a < b) return 1;
                return 0;
            }
    };

    /*
     * Used as a comparator for object T with a defined 
     * equality operator. used for constructing Max Binary Heap
     */
    template <typename T> class MaxHeapSorter
    {
        public:
            /*
             * Returns true if b is before than a, false otherwise (for maxheap)
             */
            bool before(const T& a,const T& b) const //Object T must have == operator defined properly.
            {
                if (b < a) return 1;
                return 0;
            }
    };

    /*
     * BinaryHeap queue template where T is object type of heap data and
     * C is the comparator
     */
    template <typename T, typename C> class BinaryHeap
    {
        public:
            BinaryHeap()
            {
                heap = new T[HEAP_SIZE];
                index = 0;
            }
            /* Adds T object to heap */            
            void add(const T& d) 
            {
                heap[index] = d;
                int parentIndex = int((index - 1) / 2);
                int currIndex = index;
 
                while (sorter.before(heap[currIndex], heap[parentIndex]))
                {
                    swap(heap[currIndex], heap[parentIndex]);
                    currIndex = parentIndex;
                    parentIndex = int((currIndex - 1) / 2); 
                }
                index++;
            }
            /* Pops object from heap and sets p to popped object; returns false if 
             * heap is empty*/
            bool pop(T &p)
            {
                if (index == 0) return 0;
                p = heap[0];
                heap[0] = heap[index - 1];
                index--;
                //children indexes at 2i+1 2i+2
                heapify(0);
                return 1;
            }
            /* Prints heap array in incrementing order*/
            void print()
            {
                int i;
                for (i = 0; i < index; i++)
                {
                    cout << "[" << heap[i] << "]";
                }
                cout << endl;
            }
            /* Returns true if heap is empty; false otherwise */
            bool isEmpty() const
            {
                if (index == 0) return 1;
                return 0;
            }
            /* Returns unsigned integer with size of heap */
            size_t size() const
            {
                return index;
            }

        private:
			void heapify(int i)
            {
                int l = (2 * i) + 1;
                int r = (2 * i) + 2;
                int large = i;
                
                if (l < index && sorter.before(heap[l], heap[large])) large = l;
                if (r < index && sorter.before(heap[r], heap[large])) large = r;
                swap(heap[i], heap[large]);
                if (large != i) heapify(large);
            }

            void swap(T& a, T& b)
            {
                T temp = a;
                a = b;
                b = temp;
            }

            C sorter;
            T* heap;
            int index;
    };

    /*Convenience class provides easy heap*/
    template <typename T> class MinHeap
    {
        private:
            BinaryHeap<T, MinHeapSorter<T> >* bh;
        public:
            MinHeap() {bh = new BinaryHeap<T, MinHeapSorter<T> >();}
        
            /* Pops object from heap and sets p to popped object; returns false if 
             * heap is empty*/
            bool pop(T &p) {return bh->pop(p);}
    
            /* Adds T object to heap */            
            void add(const T &d) {bh->add(d);}
    };

    /* Convenience class provides easy maxheap*/
    template <typename T> class MaxHeap
    {
        private:
            BinaryHeap<T, MaxHeapSorter<T> >* bh;
        public:
            MaxHeap() {bh = new BinaryHeap<T, MaxHeapSorter<T> >();}
            
            /* Pops object from heap and sets p to popped object; returns false if 
             * heap is empty*/ 
            bool pop(T &p) {return bh->pop(p);}
            
            /* Adds T object to heap */            
            void add(const T &d) {bh->add(d);}
    };

}
