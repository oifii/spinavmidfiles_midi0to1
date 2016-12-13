/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>


#include <ctime>
//this program uses C:\spoirier\oifii-org\httpdocs\ns-org\nsd\ar\cp\midi_commands\midi0to1\midi0to1.exe
//to convert midi files from standard midi file format 0 to format 1

//warning! this program is under construction
//todo: since midi0to1.exe does not support long filename nor long path
//it will be tricky, must either rename file to temp folder with shorth name (tested, it would work)
//or etc.
int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	//char charBuffer[2048] = {"."}; //usage: spinavmidfiles "." 0
	char charBuffer[2048] = {"C:\\spoirier\\oifii-org\\httpdocs\\ns-org\\nsd\\ar\\cp\\audio_midi\\midi-format-0"}; 
	//char charBuffer[2048] = {"testmidfolder"}; 
	if(argc>1)
	{
		//first argument is the folder name where to find .mid files
		sprintf_s(charBuffer,2048-1,argv[1]);
	}

	/////////////////////////////////////////////////////
	//execute cmd line to get all folder's .mid filenames
	/////////////////////////////////////////////////////
	string quote = "\"";
	string pathfilter;
	string path=charBuffer;
	pathfilter = path + "\\*.mid";
	string systemcommand;
	//systemcommand = "DIR " + quote + pathfilter + quote + "/B /O:N > filenames.txt";
	systemcommand = "DIR " + quote + pathfilter + quote + "/B /O:N > filenames.txt";
#ifdef _DEBUG
	cout << systemcommand << endl;
#endif //_DEBUG
	system(systemcommand.c_str());


	//////////////////////////////////////////////////////////////////////////////////////////
	//copy filename to c:\temp folder renaming files with short names, i.e. 1.mid, 2.mid, etc.
	//////////////////////////////////////////////////////////////////////////////////////////
	//todo


	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> filenames;
	ifstream ifs("filenames.txt");
	string temp;
	while(getline(ifs,temp))
		filenames.push_back(temp);


	////////////////////////////////////////////////
	//browse through filenames and call midi0to1.exe
	////////////////////////////////////////////////
	string inputfilename;
	string outputfilename;
	//stringstream ss1 (stringstream::in | stringstream::out);
	//stringstream ss2 (stringstream::in | stringstream::out);
	vector<string>::iterator it;
	cout << "filenames.txt contains:";

	
	it=filenames.begin();
	for ( it=filenames.begin() ; it < filenames.end(); it++ )
	{
		cout << *it << endl; //*it is a .mid filename

		//ss1 << fSecondsPerSegment;
		inputfilename = path + "\\" + *it;//ss1.str();
		//ss2 << numSecondsPlay;
		string filename; //without extension
		filename = (*it).substr(0,(*it).rfind('.'));
		//outputfilename = path + "\\" + *it + ".mid";//ss2.str();
		outputfilename = path + "\\" + filename + "_smf1" + ".mid";//ss2.str();

		systemcommand = "midi0to1.exe " + quote + inputfilename + quote + " " + quote + outputfilename + quote;
		cout << systemcommand << endl;
		system(systemcommand.c_str()); 
	}
	cout << endl;	
	return 0;
}