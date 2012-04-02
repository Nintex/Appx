
#include <MAUtil/Moblet.h>

#include "MAHeaders.h"


using namespace MAUtil;


#include "Html.hpp"
#include "ScrollPane.h"




class MAUIMoblet : public Moblet
{
public:

	MAUIMoblet()
	{
		//klasse die weerdata bevat, en kan updaten
		Html* html = new Html();

		//scherm klassen die data weergeven
	//	TextueelScherm* textueelScherm = new TextueelScherm( weerData );
	//	VisueelScherm* visueelScherm = new VisueelScherm( weerData );

		//geef schermen een referentie naar elkaar, zodat ze naar elkaar kunnen switchen
	//	textueelScherm->setToggleScherm( visueelScherm );
	//	visueelScherm->setToggleScherm( textueelScherm );

		//toon textueel scherm eerst
	//	textueelScherm->show();
	}


	virtual ~MAUIMoblet()
	{
	}


	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			close();
		}
	}

};



extern "C" int MAMain()
{
	Moblet::run(new MAUIMoblet());
	return 0;
}
