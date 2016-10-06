# Rabin-Karp Algorithm search substring in a string of O (N)

This algorithm is based on the lines of hashing, and those who are not familiar with the subject, refer to the [hashing algorithm in problems on the line](http://e-maxx.ru/algo/string_hashes) .

 

The authors of the algorithm - Rabin (Rabin) and Carp (Karp), 1987.

Given a string S and a text T, consisting of small Latin letters. We required to find all occurrences of the string S to the T text in time O (| S | + | T |).

Algorithm. Calculate hash string for S. Calculate hash values ​​for all line prefixes T. Now Let's brute over all the length of the substring T length | S | and each comparable to | S | in O (1).

#Implementation
	string s, t; // input data

	// Assume all powers of p
	const int p = 31;
	vector <long long> p_pow (max (s.length (), t.length ()));
	p_pow [0] = 1;
	for (size_t i = 1; i <p_pow.size (); ++ i)
		p_pow [i] = p_pow [i-1] * p;

	// Calculate the hashes of all line prefixes T
	vector <long long> h (t.length ());
	for (size_t i = 0; i <t.length (); ++ i)
	{
		h [i] = (t [i] - 'a' + 1) * p_pow [i];
		if (i) h [i] + = h [i-1];
	}

	// Calculate the hash of the string S
	long long h_s = 0;
	for (size_t i = 0; i <s.length (); ++ i)
		h_s + = (s [i] - 'a' + 1) * p_pow [i];

	// Iterate over all the length of the substring T | S | and compare them
	for (size_t i = 0; i + s.length () - 1 <t.length (); ++ i)
	{
		long long cur_h = h [i + s.length () - 1];
		if (i) cur_h - = h [i-1];
		// Give the hashes to the same extent and compare
		if (cur_h == h_s * p_pow [i])
			cout << i << '';
	}