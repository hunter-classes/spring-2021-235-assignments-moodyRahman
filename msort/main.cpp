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

