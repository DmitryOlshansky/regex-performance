import core.stdc.string;
import core.runtime;
import std.regex;

struct D_Regex{}

__gshared bool inited = false;


Regex!char* root = null; // to keep away GC

extern(C) D_Regex* new_regex(const char* pattern)
{
	if (!inited) {
		inited = true;
	}
	auto pat = pattern[0..strlen(pattern)];
	try{
		Regex!char* r = new Regex!char;
		*r = regex(pat);
		root = r;
		return cast(D_Regex*)r;
	}
	catch(Exception e){
		return null;
	}
}

extern(C) ulong find_matches(D_Regex* regex, const char* input, ulong length)
{
	ulong count = 0;
	auto src = input[0..length];
	Regex!char* r = cast(Regex!char*)regex;
	foreach(m; matchAll(src, *r)){
		count++;
	}
	return count;
}