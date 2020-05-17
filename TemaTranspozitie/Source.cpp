#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <numeric>

void PrintMatrix(std::vector<std::vector<std::string>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void CreateFirstTwoLines(std::vector<std::string> v, std::vector<std::vector<std::string>>& matrix, std::vector<int>& vectOfIndices)
{
	for (int i = 0; i < matrix[0].size(); i++)
	{
		auto pos = std::find(v.begin(), v.end(), matrix[0][i]);
		auto index = std::distance(v.begin(), pos);
		vectOfIndices.push_back(index + 1);
	}

	std::vector<std::string> vectOfStringToAddInMatrix;

	for (auto c : vectOfIndices)
	{
		vectOfStringToAddInMatrix.push_back(std::to_string(c));
	}

	matrix.push_back(vectOfStringToAddInMatrix);
	std::cout << "\n";
}

void CreateRestOfTheMatrix(std::vector<std::vector<std::string>>& matrix, std::vector<std::string> vect)
{
	int i = 0;

	bool ok = false;

	std::vector<std::string> v1;

	for (auto word : vect)
	{
		for (auto c : word)
		{
			std::string s(1, c);
			v1.push_back(s);
			i++;
			if (i == matrix[0].size())
			{
				matrix.push_back(v1);
				v1.clear();
				ok = false;
				i = 0;
			}
		}
	}

	std::vector<char> alphabet(26);
	std::iota(alphabet.begin(), alphabet.end(), 'A');

	int index = 0;
	if (i != 0)
	{
		while (i < matrix[0].size())
		{
			std::string s(1, alphabet[index]);
			v1.push_back(s);
			index++;
			i++;
		}
		matrix.push_back(v1);
	}
	PrintMatrix(matrix);
}

void CreateTheCryptedMessage(std::vector<std::vector<std::string>> matrix, std::vector<int> vectOfIndices, std::vector<std::string>& cryptedText)
{
	std::sort(vectOfIndices.begin(), vectOfIndices.end());
	for (auto index : vectOfIndices)
	{
		auto pos = std::find(matrix[1].begin(), matrix[1].end(), std::to_string(index));
		auto posExact = std::distance(matrix[1].begin(), pos);

		for (int i = 2; i < matrix.size(); i++)
		{
			cryptedText.push_back(matrix[i][posExact]);
		}
	}
}

int main()
{
	std::ifstream f("input.txt");

	std::string key;
	f >> key;
	for (auto c : key)
	{
		if (std::count(key.begin(), key.end(), c) > 1)
		{
			std::cout << "Cheia contine litere care se repeta. Introduceti alta cheie in fisierul text input!\n";
			return 0;
		}
	}
	std::cout << "Key: ";
	std::cout << key;

	std::vector<std::string> textV;
	std::string text;
	while (!f.eof())
	{
		f >> text;
		textV.push_back(text);
	}
	std::cout << "\nText: ";
	for (auto c : textV)
	{
		std::cout << c << " ";
	}

	std::vector<std::vector<std::string>> matrix;
	std::vector<std::string> vect;
	for (char c : key)
	{
		std::string s(1, c);
		vect.push_back(s);
	}
	matrix.push_back(vect);

	std::sort(vect.begin(), vect.end());
	std::vector<int> vectOfIndices;

	CreateFirstTwoLines(vect, matrix, vectOfIndices);

	CreateRestOfTheMatrix(matrix, textV);

	std::vector<std::string> cryptedText;

	CreateTheCryptedMessage(matrix, vectOfIndices, cryptedText);

	std::cout << "\nText criptat: ";
	for (auto c : cryptedText)
	{
		std::cout << c << " ";
	}
	std::cout << "\n";
}