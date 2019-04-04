from collections import defaultdict
from copy import deepcopy

heap_steps = defaultdict()


def reset_steps():
    heap_steps.clear()


class Heap:
    arr = []
    arr_size = 0
    size = 0

    def __init__(self, arr, arr_size, heap_size):
        self.arr = arr
        self.arr_size = arr_size
        self.size = heap_size


def max_heapify(heap, i):
    largest_idx = i
    l_idx, r_idx = None, None

    if 2 * i + 1 < heap.size:
        l_idx = 2 * i + 1

    if 2 * (i + 1) < heap.size:
        r_idx = 2 * (i + 1)

    if l_idx is not None and heap.arr[l_idx] > heap.arr[i]:
        largest_idx = l_idx

    if r_idx is not None and heap.arr[r_idx] > heap.arr[largest_idx]:
        largest_idx = r_idx

    if largest_idx != i:
        heap.arr[i], heap.arr[largest_idx] = heap.arr[largest_idx], heap.arr[i]
        max_heapify(heap, largest_idx)


def build_max_heap(heap):
    for i in range(int(heap.arr_size / 2), -1, -1):
        max_heapify(heap, i)


def heapsort(arr):
    n = 1
    reset_steps()

    arr_size = len(arr)
    heap_size = arr_size

    heap = Heap(arr, arr_size, heap_size)

    build_max_heap(heap)

    heap_steps[n] = deepcopy(heap)

    for i in range(heap.arr_size - 1, 0, -1):
        heap.arr[i], heap.arr[0] = heap.arr[0], heap.arr[i]
        heap.size -= 1
        max_heapify(heap, 0)

        n += 1
        heap_steps[n] = deepcopy(heap)

    return heap.arr


def get_heap_steps():
    return heap_steps


if __name__ == "__main__":
    array = [17, 9, 13, 8, 7, -5, 6, 11, 3, 4, 1, 2]
    heap_sort(array)
    print(array)
