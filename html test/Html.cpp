/*
 * WeerData.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "Html.hpp"
#include <stdio.h>
#include <stdlib.h>


//hulpfunctie
char* zoekWoord(char* buffer, char* testString)
{
	//zoekt de beginpositie van testString als die voorkomt in buffer
	char* myPos = strstr( buffer, testString );

	if(myPos == NULL)
	{
		return NULL;
	}

	else
	{
		//geef de positie terug achter de gevonden string
		return( myPos + strlen(testString) );
	}
}



Html::Html() : HttpConnection( this )
{
	//stel de isConnecting boolean in op 'in gebruik'
	this->isConnecting = true;

	//maak een nieuwe connectie
	this->url = "http://www.thisiswhyimbroke.com";
    int res = this->create( url, HTTP_GET );

    //foutafhandeling bij connectie probleem
    if(res < 0)
    {
        lprintfln( "unable to connect - %i\n", res );
    }

    else
    {
    	this->finish();
    }

    //reset de weerdata naar 0
	for( int i = 0; i < 3; i++ )
	{
		this->zonneschijn[i] = 0;
		this->neerslag[i] = 0;
		this->minimumtemperatuur[i] = 0;
	}
}

Html::~Html()
{

}


void Html::update()
{
	//update alleen als er niet momenteel al een update uitgevoerd wordt
	if( this->isConnecting == false )
	{
		//stel de isConnecting boolean in op 'in gebruik'
		this->isConnecting = true;

		//maak een nieuwe connectie
		this->connect( this->url );
	}
}




void Html::httpFinished( HttpConnection* http, int result )
{
	//stel de isConnecting boolean in op 'in gebruik'
	this->isConnecting = true;

	//recv() leest maximaal 1024 bytes (staat in CONNECTION_BUFFER_SIZE)
	this->recv(weerDataRecv, 1024);
}


void Html::connRecvFinished( Connection* conn, int result )
{
	weerDataRecv[result]= '\0';

	//Prints raw html data to screen.
		printf(weerDataRecv);

	//blijf lezen met 1024 bytes (zie onder) tot result einde van de site heeft bereikt (waarbij result < 0)
    if(result >= 0)
    {


        //lees de volgende 1024 bytes, deze functie wordt dan weer opnieuw aangeroepen
        this->recv(weerDataRecv, CONNECTION_BUFFER_SIZE);
    }

    else
    {
    	//fout is opgetreden of we hebben het eind van het document bereikt, sluit af.
    	this->close();
    }
}


void Html::connReadFinished( Connection* conn, int result )
{
}


void Html::connectFinished(Connection* conn, int result)
{
	//connectie is geeindigd, geef connectie weer vrij met de isConnecting boolean
	this->isConnecting = false;
}


