#include <iostream>
#include <vector>

std::vector<int> msort(std::vector<int> left, std::vector<int> right)
{
	std::vector<int> out;
	auto lindex = left.begin();
	auto rindex = right.begin();

	// compare the first elements of each sub vector until you hit the end of one
	while (lindex != left.end() && rindex != right.end())
	{

		if (*(lindex) <= *(rindex))
		{
			out.push_back(*(lindex++));
		}
		else
		{
			out.push_back(*(rindex++));
		}
	}

	// if there's a remaining elements in either vector, fully flush them out
	if (lindex == left.end())
	{
		while (rindex != right.end())
		{
			out.push_back(*(rindex++));
		}
	}

	if (rindex == right.end())
	{
		while (lindex != left.end())
		{
			out.push_back(*(lindex++));
		}
	}

	return out;
}

std::vector<int> merge(std::vector<int> in)
{
	if (in.size() == 0 || in.size() == 1)
	{
		return in;
	}
	if (in.size() == 2)
	{
		if (in[0] > in[1])
		{
			int x = in[1];
			in[1] = in[0];
			in[0] = x;
			return in;
		}
		return in;
	}

	int mid = in.size()/2;

	auto left = merge(std::vector<int>(in.begin(), in.begin()+mid));
	auto right = merge(std::vector<int>(in.begin()+mid, in.end()));

	return msort(left, right);

}

int main()
{
	std::vector<int> left = {0, 9, 20};
	std::vector<int> right = {4, 5, 6, 7, 8, 9};

	std::vector<int> arr = {1, 5, 8, 7, 8, 3, 4, 2, 4, 6, 9, 7, 6, 4, 3, 1, 5, 6, 3, 8, 2, 9};

	std::vector<int> out = merge(arr);

	for (auto x : out)
	{
		std::cout << x << ", ";
	}
	std::cout << "" << std::endl;
}