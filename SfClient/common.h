#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct Vendors{
	QString vendorUrl ;
	QString vendorName;
	QString vendorPassword;
	QString vendorLoginName;
	QString	vendorFactory;
	Vendors()
	{
		vendorUrl = "";
		vendorName = "";
		vendorPassword = "";
		vendorLoginName = "";
		vendorFactory = "midea";
	}
}Vendors;


#endif