#ifndef __HTMLPARSER_HPP__
#define __HTMLPARSER_HPP__

#include <string>
#include <iostream>

namespace htmlparser
{
	template <class InputIterator, class RangeIterator>
	constexpr InputIterator search(InputIterator first1, InputIterator last1, RangeIterator first2, RangeIterator last2)
	{
		RangeIterator tag_itr = first2;
		for ( ; first1 != last1; ++first1)
		{
			if (*first1 == *tag_itr)
			{
				for (InputIterator itr = first1;
					itr != last1 && tag_itr != last2 && *itr == *tag_itr;
					++itr, ++tag_itr);
				if (tag_itr == last2) return first1;
				else tag_itr = first2;
			}
		}
		return last1;
	}

	template <class InputIterator, class stringT, class charT>
	bool find(InputIterator first, InputIterator last, stringT& out, const charT& tag)
	{
		using namespace std::string_literals;

		const std::string begin_tag = "<"s + tag + ">";
		InputIterator begin_tag_itr = htmlparser::search(first, last, begin_tag.begin(), begin_tag.end());
		if (begin_tag_itr == last) return false;

		const std::string end_tag = "</"s + tag + ">";
		InputIterator end_tag_itr = htmlparser::search(begin_tag_itr+begin_tag.size(), last, end_tag.begin(), end_tag.end());
		if (end_tag_itr == last) return false;

		std::copy(begin_tag_itr+begin_tag.size(), end_tag_itr, std::back_inserter(out));
		return true;
	}

	template <class InputIterator, class OutputVector, class TagString, class ClassString=std::string>
	bool find_all(InputIterator first, InputIterator last, OutputVector& out, const TagString& tag, const ClassString& class_="NULL")
	{
		using namespace std::string_literals;

		std::string begin_tag;
		if (class_ == "NULL")
			begin_tag = "<"s + tag + ">";
		else
			begin_tag = "<"s + tag + " class=\"" + class_ + "\">";
		const std::string end_tag = "</"s + tag + ">";

		while (true)
		{
			InputIterator begin_tag_itr = htmlparser::search(first, last, begin_tag.begin(), begin_tag.end());
			if (begin_tag_itr == last) break;
			InputIterator end_tag_itr = htmlparser::search(begin_tag_itr+begin_tag.size(), last, end_tag.begin(), end_tag.end());
			if (end_tag_itr == last)   break;

			first = end_tag_itr;

			std::string result;
			std::copy(begin_tag_itr+begin_tag.size(), end_tag_itr, std::back_inserter(result));
			out.push_back(result);
		}

		if (out.size() == 0) return false;
		else                 return true;
	}
}

#endif
