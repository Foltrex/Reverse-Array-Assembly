#include <iostream>
#include <fstream>

void reverseArrayC(int* const arr, int n)
{
	for (int low = 0, high = n - 1; low < high; low++, high--)
	{
		int temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
}

void reverseArrayASM(int* const mass, unsigned msize) {
	_asm {
		mov esi, [mass]
		mov ecx, msize
		lea edi, [esi + ecx * 4 - 4]
		cmp esi, edi
		jnb done
		next :
		mov eax, [esi]
			mov ebx, [edi]
			mov[edi], eax
			mov[esi], ebx

			add esi, 4
			sub edi, 4
			cmp esi, edi
			jb next
			done :
	}
}

void printArray(std::ostream& out, int* const arr, const int SIZE) {
	for (auto it = arr; it != arr + SIZE; ++it) {
		out << *it << " ";
	}
	out << '\n';
}

int main() {
	int arr[] = { 1 };
	int arr2[] = { 1 };
	const int SIZE = (sizeof(arr) / sizeof(arr[0]));

	std::ofstream fout("output.txt");

	std::cout << "Source array:\n";
	printArray(std::cout, arr, SIZE);
	printArray(std::cout, arr2, SIZE);

	fout << "Source array:\n";
	printArray(fout, arr, SIZE);
	printArray(fout, arr2, SIZE);

	reverseArrayASM(arr, SIZE);
	reverseArrayC(arr2, SIZE);

	std::cout << '\n' << "Reverse array:\n";
	printArray(std::cout, arr, SIZE);
	printArray(std::cout, arr2, SIZE);

	fout << '\n' << "Reverse array:\n";
	printArray(fout, arr, SIZE);
	printArray(fout, arr2, SIZE);
}

