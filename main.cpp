#include "mylib.h"
#include <bits/stdc++.h>

using namespace std;

void read(FILE* fin, const char* str, int match_length)
{
	char buf[65536];
	int counter=0;
	while(fgets(buf,32,fin)!=NULL)
	{
		if(strncmp(buf,str,match_length)!=0)continue;
		fgets(buf,65536,fin);
		printf("%s",buf);
		++counter;
	}
	printf("%d results found\n",counter);
}



int main(int args, char** argv)
{
	if(args!=2)
	{
		fprintf(stderr,"Usage: ./smiles file.sdf\n");
		return 1;
	}
	char* fname = argv[1];
	FILE* fin = fopen(fname,"r");
	//read(fin,"> <PUBCHEM_OPENEYE_ISO_SMILES>\n");
	read(fin,"> <PUBCHEM_IUPAC_INCHI>\n",23);
}