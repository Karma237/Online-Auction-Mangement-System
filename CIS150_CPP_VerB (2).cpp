#include <iostream>
#include <string>
#include <algorithm>                                        //for transform function
using namespace std;

int activeACCOUNTS = 6;                                    //global counter that counts number of used accounts
int i = 0, j = 0;

struct date
{
	int day, month, year;
};

struct BUYING_REQUEST
{
	string nameofBUYER;
	string showREQUEST;
	int bidpriceREQUEST;
	bool BUYINGREQUESTS = false;
};                                                       //used to send a buying request at buying rquest function

struct items
{
	string CATEGORY, NAME, statues;
	int itemNUM, STARTING_BID_PRICE;
	date START_DATE, END_DATE;
	BUYING_REQUEST BUYER1, BUYER2;
};                                                         //stores items information

struct USERS
{
	string  NAME, ID, EMAIL, deliveryADDRESS;
	int PW, POINTS, phoneNUMBER;
	items listofITEMS[10];
} MYACCOUNT, listofMEMBERS[30];                            //stores members informations

void login(string ID, int  PW)
{
	string login = "yes";
	bool isA_MEMBER = false;                              //checking if the user entered PW/ID is of available member

	while (login == "yes")
	{
		cout << "Please type your account ID" << endl << "____________" << endl;
		cin >> ID;   cout << "*******" << endl;
		cout << "Please type your account PASSWORD" << endl << "____________" << endl;
		cin >> PW; cout << "*******" << endl;

		for (i = 0; i < activeACCOUNTS; i++)
		{
			if (ID == listofMEMBERS[i].ID && PW == listofMEMBERS[i].PW)
			{
				MYACCOUNT = listofMEMBERS[i];
				cout <<
					"========================" << endl
					<< "Succesfully loged in " << endl
					<< "========================" << endl;
				cout << endl << "********** WELCOME **********" << endl
					<< MYACCOUNT.NAME << endl
					<< "MY Points: " << MYACCOUNT.POINTS << endl;

				login = "no";
				isA_MEMBER = true;
			}
		}

		if (isA_MEMBER == false)
		{
			cout << "PW or ID is incorrect , Please TRY AGAIN" << endl << endl;
			login = "yes";                                                //cheking if user id and pw exists
		}

		cout << "=============================================" << endl;
	}
	return;
}

void myREQUESTS_AND_SOLD_ITEMS(int profile)                //inform buyer if thier request approved or rejected/ seller if item sold  
{
	bool isavailable_REQUEST = false;                        //checking if thier is any requests for active now user
	bool hadSOLD = false;                                //checking if active now user had sold any item before

	if (profile == 1)
	{
		for (i = 0; i < activeACCOUNTS; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (MYACCOUNT.NAME == listofMEMBERS[i].listofITEMS[j].BUYER1.nameofBUYER)
				{
					if (listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST == "APPROVED")
						cout << "YOUR REQUEST HAS BEEN APPROVED" << endl;

					else if (listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST == "REJECTED")
						cout << "YOUR REQUEST HAS BEEN REJECETED" << endl;

					else if (listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST == "SENT")
						cout << "YOUR REQUEST HAS BEEN SENT ,PLEASE WAIT FOR THE RESPONSE" << endl;

					isavailable_REQUEST = true;
				}

				else if (MYACCOUNT.NAME == listofMEMBERS[i].listofITEMS[j].BUYER2.nameofBUYER)
				{
					if (listofMEMBERS[i].listofITEMS[j].BUYER2.showREQUEST == "APPROVED")
						cout << "YOUR REQUEST HAS BEEN APPROVED" << endl;

					else if (listofMEMBERS[i].listofITEMS[j].BUYER2.showREQUEST == "REJECTED")
						cout << "YOUR REQUEST HAS BEEN REJECETED" << endl;

					isavailable_REQUEST = true;
				}
			}
		}

		if (isavailable_REQUEST == false)
		{
			cout << "THIER IS NO REQUESTS" << endl;
		}
	}
	else
		if (profile == 2)
		{
			cout << endl << "----------Your Sold Items History----------" << endl;

			for (i = 0; i < activeACCOUNTS; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (MYACCOUNT.ID == listofMEMBERS[i].ID)
					{
						if (listofMEMBERS[i].listofITEMS[j].statues == "SOLD")
						{
							cout << j + 1 << "Item: " << listofMEMBERS[i].listofITEMS[j].NAME << endl
								<< "Sold Date: " << listofMEMBERS[i].listofITEMS[j].END_DATE.day
								<< "/" << listofMEMBERS[i].listofITEMS[j].END_DATE.month << endl
								<< "____________________________________________________" << endl;
							hadSOLD = true;
						}
					}
				}
			}
			if (hadSOLD == false)
			{
				cout << endl << "You have not sell any item yet" << endl;
			}

		}
		else
		{
			cout << "Invalid entry, Please choose either[1]or [2]" << endl;
		}
	return;
}

void SEARCH(string s_by, string s_Category, int sPRICE)
{
	bool isAvailable_ITEM = false;                          //checking if the required item that user type is available in the market

	cout << "DO you want to search by category or price?" << endl;
	cin >> s_by;
	transform(s_by.begin(), s_by.end(), s_by.begin(), tolower);      //convert all letters to lower to validate user input

	if (s_by == "category")
	{
		cout << "Enter category:" << endl;
		cin >> s_Category;
		transform(s_Category.begin(), s_Category.end(),
			s_Category.begin(), toupper);                     //convert letters to upper as all categories written in upper case
		cout << "*****************" << endl;

		for (i = 0; i < activeACCOUNTS; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (listofMEMBERS[i].listofITEMS[j].statues == "AVAILABLE"
					&& s_Category == listofMEMBERS[i].listofITEMS[j].CATEGORY)
				{
					cout << "category: " << listofMEMBERS[i].listofITEMS[j].CATEGORY << endl
						<< "item:" << listofMEMBERS[i].listofITEMS[j].NAME << endl
						<< "item number: " << listofMEMBERS[i].listofITEMS[j].itemNUM << endl
						<< "Starting price is: " << listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE << endl
						<< "Starting Auction Date: " << listofMEMBERS[i].listofITEMS[j].START_DATE.day << '/'
						<< listofMEMBERS[i].listofITEMS[j].START_DATE.month << '/'
						<< listofMEMBERS[i].listofITEMS[j].START_DATE.year << endl
						<< "Ending Auction Date: " << listofMEMBERS[i].listofITEMS[j].END_DATE.day
						<< '/' << listofMEMBERS[i].listofITEMS[j].END_DATE.month << '/'
						<< listofMEMBERS[i].listofITEMS[i].END_DATE.year << endl
						<< "Statues: " << listofMEMBERS[i].listofITEMS[j].statues << endl <<
						"______________________________" << endl;
					isAvailable_ITEM = true;
				}
			}
		}
	}
	else if (s_by == "price")
	{
		cout << "Enter price [in numbers]: " << endl;
		cin >> sPRICE;
		cout << "*****************" << endl;

		for (i = 0; i < activeACCOUNTS; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (listofMEMBERS[i].listofITEMS[j].statues == "AVAILABLE"
					&& sPRICE == listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE)
				{
					cout << "category: " << listofMEMBERS[i].listofITEMS[j].CATEGORY << endl
						<< "item:" << listofMEMBERS[i].listofITEMS[j].NAME << endl
						<< "item number: " << listofMEMBERS[i].listofITEMS[j].itemNUM << endl
						<< "Starting price is: " << listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE << endl
						<< "Starting Auction Date: " << listofMEMBERS[i].listofITEMS[j].START_DATE.day << '/'
						<< listofMEMBERS[i].listofITEMS[j].START_DATE.month << '/'
						<< listofMEMBERS[i].listofITEMS[j].START_DATE.year << endl
						<< "Ending Auction Date: " << listofMEMBERS[i].listofITEMS[j].END_DATE.day
						<< '/' << listofMEMBERS[i].listofITEMS[j].END_DATE.month << '/'
						<< listofMEMBERS[i].listofITEMS[i].END_DATE.year << endl
						<< "Statues: " << listofMEMBERS[i].listofITEMS[j].statues << endl <<
						"______________________________" << endl;
					isAvailable_ITEM = true;
				}
			}
		}
	}

	if (isAvailable_ITEM == false)
	{
		cout << "SORRY, THERE IS NO AVAILABLE ITEMS" << endl;
	}
	return;
}

void BUYING(string required, char bapprove)
{

	cout << "Enter required item for buying: " << endl;
	cin >> required;
	transform(required.begin(), required.end(),
		required.begin(), tolower);                      //convert all letters to lower as all items are written lower case
	for (i = 0; i < activeACCOUNTS; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (required == listofMEMBERS[i].listofITEMS[j].NAME &&
				listofMEMBERS[i].listofITEMS[j].statues == "AVAILABLE")
			{
				if (listofMEMBERS[i].listofITEMS[j].BUYER1.BUYINGREQUESTS == true)
				{
					cout << "starting bid price is :" << listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE << endl;
					cout << "The seller of the chosen items" << endl
						<< "Name is: " << listofMEMBERS[i].NAME << endl
						<< "PHONE NUMBER IS: " << listofMEMBERS[i].phoneNUMBER << endl
						<< "POINTS got from other members feedback is: " << listofMEMBERS[i].POINTS << endl;

					cout << "DO YOU WANT TO BUY THIS ITEM WITH SELLER REQUIRED PRICE ,Type [y/n]" << endl;
					cin >> bapprove;
					cout << "*****************" << endl;

					if (bapprove == 'y')
					{
						listofMEMBERS[i].listofITEMS[j].statues = "SOLD";
						cout << "CONGRATULATIONS, SUCCESFULLY BOUGHT" << endl;
						listofMEMBERS[i].listofITEMS[j].statues = "SOLD";
						listofMEMBERS[i].listofITEMS[j].BUYER2.showREQUEST = "APPROVED";
						listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST = "REJECTED";

					}
					if (bapprove == 'n')
					{
						listofMEMBERS[i].listofITEMS[j].BUYER2.nameofBUYER = MYACCOUNT.NAME;
						cout << "ENTER PRICE:" << endl;
						cin >> listofMEMBERS[i].listofITEMS[j].BUYER2.bidpriceREQUEST;

						if (listofMEMBERS[i].listofITEMS[j].BUYER1.bidpriceREQUEST >
							listofMEMBERS[i].listofITEMS[j].BUYER2.bidpriceREQUEST)
						{
							cout << "We are SORRY to inform you that the item has been sold to another member" << endl;
							listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST = "APPROVED";
							listofMEMBERS[i].listofITEMS[j].BUYER2.showREQUEST = "REJECTED";
							listofMEMBERS[i].listofITEMS[j].statues = "SOLD";
						}

						else
						{
							cout << "CONGRATULATIONS, SUCCESFULLY BOUGHT" << endl;
							listofMEMBERS[i].listofITEMS[j].statues = "SOLD";
							listofMEMBERS[i].listofITEMS[j].BUYER2.showREQUEST = "APPROVED";
							listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST = "REJECTED";
						}
					}
				}
				else
				{
					cout << "starting bid price is :" << listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE << endl;
					cout << "The seller of the chosen items" << endl << "Name is: " << listofMEMBERS[i].NAME << endl
						<< "PHONE NUMBER IS: " << listofMEMBERS[i].phoneNUMBER << endl
						<< "POINTS got from other members feedback is: " << listofMEMBERS[i].POINTS << endl;
					cout << "DO YOU WANT TO BUY THIS ITEM WITH SELLER REQUIRED PRICE ,Type [y/n]" << endl;

					cin >> bapprove;
					cout << "*****************" << endl;
					if (bapprove == 'y')
					{
						cout << "CONGRATULATIONS, SUCCESFULLY BOUGHT" << endl;
						listofMEMBERS[i].listofITEMS[j].statues = "SOLD";
					}

					if (bapprove == 'n')
					{
						cout << "ENTER PRICE:" << endl;
						listofMEMBERS[i].listofITEMS[j].BUYER1.nameofBUYER = MYACCOUNT.NAME;
						cin >> listofMEMBERS[i].listofITEMS[j].BUYER1.bidpriceREQUEST;
						listofMEMBERS[i].listofITEMS[j].BUYER1.showREQUEST = "SENT";
						cout << "YOUR BID REQUEST HAS BEEN SENT" << endl;
						listofMEMBERS[i].listofITEMS[j].BUYER1.BUYINGREQUESTS = true;
					}
				}
			}
		}
	}
	return;
}

void SELLING(int numberofItems)
{
	cout << "PLEASE ENTER THE NUMBER OF ITEMS YOU SELLED/ OFFERED IN MARKET PLACE" << endl
		<< " For the first time type 0\n Second time type 1\n Third time type 2\n etc..." << endl;
	cin >> numberofItems;
	cout << "************" << endl;
	for (i = 0; i < 30; i++)
	{
		if (listofMEMBERS[i].NAME == MYACCOUNT.NAME)
		{
			cout << "Type name of the item: ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].NAME;
			cout << endl << "_____________________________________" << endl;

			cout << "Choose the category of the item [Type your choice as shown]: "
				<< endl << "CLOTHES/ FURNITURE/ BOOKS/ ARTS/ ACCESSORIES: ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].CATEGORY;

			transform(listofMEMBERS[i].listofITEMS[numberofItems].CATEGORY.begin(),
				listofMEMBERS[i].listofITEMS[numberofItems].CATEGORY.end(),
				listofMEMBERS[i].listofITEMS[numberofItems].CATEGORY.begin(), toupper);  /*converting all letters to upper case
																						  to keep the symmetry in market place
																						 & Helps in searching by category function
																						 as all categories are written upper case
																						 thus user search by upper case*/

			cout << endl << "_____________________________________" << endl;

			cout << "Type a [number] for your item : ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].itemNUM;
			cout << endl << "_____________________________________" << endl;

			transform(listofMEMBERS[i].listofITEMS[numberofItems].NAME.begin(),
				listofMEMBERS[i].listofITEMS[numberofItems].NAME.end(),
				listofMEMBERS[i].listofITEMS[numberofItems].NAME.begin(), tolower);     //same as category but to lower case

			cout << "Type required starting bid price: ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].STARTING_BID_PRICE;
			cout << endl << "_____________________________________" << endl;

			cout << "Type the start date to be showed, PLEASE TYPE DAY THEN MONTH: ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].START_DATE.day
				>> listofMEMBERS[i].listofITEMS[numberofItems].START_DATE.month;
			listofMEMBERS[i].listofITEMS[numberofItems].START_DATE.year = 2020;
			cout << "_____________________________________" << endl;

			cout << "Type the end date ,PLEASE TYPE DAY THEN MONTH: ";
			cin >> listofMEMBERS[i].listofITEMS[numberofItems].END_DATE.day
				>> listofMEMBERS[i].listofITEMS[numberofItems].END_DATE.month;
			listofMEMBERS[i].listofITEMS[numberofItems].END_DATE.year = 2020;
			listofMEMBERS[i].listofITEMS[numberofItems].statues = "AVAILABLE";

			cout << endl << "Congratulations, The item is now offered in the market place" << endl;
		}
	}
	return;
}

struct storedCATEGORES {
	string nameofCATEGORY;
	int numofCATEGORY;
} topCATEGORY, myCATEGORIES[5];

void MONTHLY_REPORT()                                        //most selled category for entered month
{
	int month = 0;          topCATEGORY = myCATEGORIES[0];

	myCATEGORIES[0] = { "CLOTHES", 0 }; myCATEGORIES[1] = { "FURNITURE", 0 }; myCATEGORIES[2] = { "BOOKS" , 0 };
	myCATEGORIES[3] = { "ACCESSORIES", 0 }; myCATEGORIES[4] = { "ARTS", 0 };

	cout << "Enter required month to show the report" << endl;
	cin >> month; cout << "**********" << endl;

	for (i = 0; i < activeACCOUNTS; i++)
	{
		for (j = 0; j < 10; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (listofMEMBERS[i].listofITEMS[j].statues == "SOLD"
					&& listofMEMBERS[i].listofITEMS[j].END_DATE.month == month
					&& listofMEMBERS[i].listofITEMS[j].CATEGORY == myCATEGORIES[k].nameofCATEGORY)
				{
					myCATEGORIES[k].numofCATEGORY++;
				}

				if (myCATEGORIES[k].numofCATEGORY > topCATEGORY.numofCATEGORY)
				{
					topCATEGORY.numofCATEGORY = myCATEGORIES[k].numofCATEGORY;
					topCATEGORY.nameofCATEGORY = myCATEGORIES[k].nameofCATEGORY;
				}
			}
		}
	}
	if (topCATEGORY.numofCATEGORY >= 1)
	{
		cout << " The top selled category for this month [" << month << "] is "
			<< topCATEGORY.nameofCATEGORY << endl << endl;
	}
	else
	{
		cout << " THERE IS NO SOLD ITEMS FOR THIS MONTH YET ,PLEASE TRY LATER " << endl;
	}
	return;
}

void FEEDBACK(string F, string id, int r)
{
	bool isAVAILABLE_ID = false;                                   //checking if entered ID exists in the program
	cout << "Please enter the other person's ID: ";
	cin >> id;
	cout << "******************" << endl;
	for (i = 0; i < activeACCOUNTS; i++)
	{
		if (id == listofMEMBERS[i].ID)
		{
			cout << "Please write your feedback " << endl;
			cin.ignore();
			getline(cin, F);
			cout << "**************************" << endl;
			cout << "NOW PLEASE RATE HIM/HER FROM 1 TO 5" << endl;
			cin >> r;
			cout << "**********" << endl;
			if (r > 3)
				listofMEMBERS[i].POINTS++;

			cout << "THANK YOU" << endl << endl;
			isAVAILABLE_ID = true;
		}
	}
	if (isAVAILABLE_ID == false)
	{
		cout << "No member with this ID" << endl;
	}
	return;
}

void REGISTER(int& acc)
{
	if (acc < 30)
	{
		acc++;                            //increament golabal variable accounts before creating new account

		cout << "To create a new account , please fill the folloing data" << endl
			<< "______________________________________" << endl;

		cout << "PLEASE , Type your Name:  ";
		cin >> listofMEMBERS[acc].NAME;
		cout << "______________________________________" << endl;

		cout << "PLEASE , Tupe your Gmail address:  ";
		cin >> listofMEMBERS[acc].EMAIL;
		cout << "______________________________________" << endl;

		cout << "PLEASE , Create your own ID:  ";
		cin >> listofMEMBERS[acc].ID;
		cout << "______________________________________" << endl;

		cout << "PLEASE , create your own Password [[in numbers]] :  ";
		cin >> listofMEMBERS[acc].PW;
		cout << "______________________________________" << endl;

		cout << "PLEASE , Type required Delivery address:  ";
		cin >> listofMEMBERS[acc].deliveryADDRESS;
		cout << "______________________________________" << endl;

		cout << "PLEASE , Type your Phone number:  ";
		cin >> listofMEMBERS[acc].phoneNUMBER;
		cout << "______________________________________" << endl;
	}
	return;
}

int main() {

	listofMEMBERS[0] = { "Albert Christ", "_albert", "Albert_christ@gmail.com", "Cairo ,Egypt", 2371, 2, 43211 ,
	{
		 { "CLOTHES", "tshirt", "AVAILABLE", 1, 150, { 24, 4, 2020 }, { 5, 5, 2020 } } ,
		 { "CLOTHES", "bag", "AVAILABLE", 3, 400, { 21, 3, 2020 }, { 3, 4, 2020 } },
		 { "FURNITURE", "chair", "AVAILABLE", 7, 800, { 12, 3, 2020 }, { 27, 4, 2020 } },
		 { "BOOKS", "1984", "AVAILABLE", 2, 120, { 11, 4, 2020 }, {17, 4, 2020 }  }
	}
	};
	listofMEMBERS[1] = { "John Adam", "john", "john17@gmail.com", "Alexandria ,Egypt", 4122, 4, 32134,
		{
		  {"ACCESSORIES","necklace", "AVAILABLE", 5, 300, { 15, 4, 2020 }, { 11, 5, 2020 }},
		  {"ACCESSORIES", "earrings", "SOLD", 4, 200, { 11, 3, 2020 }, { 12, 4, 2020 } }
		 }
	};
	listofMEMBERS[2] = { "Ayla", "3_ayla", "Ayla2000@gmail.com", "Cairo ,Egypt", 2920, 2, 21234,
		{
		  {"FURNITURE", "tv", "SOLD", 6, 15000, { 17, 2, 2020 }, { 2, 4, 2020 } } ,
		  {"FURNITURE", "Table", "SOLD", 8, 600, { 12, 4, 2020 }, {4, 4, 2020 } },
		  {"BOOKS", "psychology", "AVAILABLE", 11, 300, { 14, 4, 2020 }, { 22, 5, 2020 } }
		}
	};
	listofMEMBERS[3] = { "Mia", "1@mia", "Meraa19@gmail.com", "Giza ,Egypt", 2511, 3, 19765,
		{
			{"ARTS", "portrait", "SOLD", 33, 300, { 17, 1, 2020 }, { 25, 1, 2020 } },
			{ "ARTS", "portrait", "SOLD", 31, 280, { 2, 1, 2020 }, { 7, 2, 2020 } },
			{"BOOKS", "glass",  "SOLD" , 22, 180, {5, 3, 2020 }, { 17, 3, 2020 } },
			{ "CLOTHES", "Tshirt", "SOLD", 23, 200, { 17, 5, 2020 }, { 2, 5, 2020 } }

		}
	};

	listofMEMBERS[4] = { "Malek Ali", "malek_", "Malek_A@gmail.com", "Alexandria ,Egypt", 1311, 0, 32145 };
	listofMEMBERS[5] = { "Nathalie Drake", "N_Drake", "Nathalie_drake@gmail.com", "Cairo, Egypt", 1575, 0, 87654 };

	char goBACK = 'E';
	int mainmenuCHOICE;

	while (goBACK == 'E' || goBACK == 'e')
	{

		cout << "1.LOGIN , To enter your account" << endl
			<< "________________________________" << endl
			<< "2.SIGNUP , To create a new account" << endl
			<< "________________________________" << endl;

		cout << endl << "TYPE YOUR CHOICE IN THE FORM OF A NUMBER"
			<< endl << "=======================================" << endl;
		cin >> mainmenuCHOICE;
		cout << "*****************" << endl << endl;

		if (mainmenuCHOICE == 1)
		{
			string userID; int userPW = 0;
			login(userID, userPW);
		}
		else if (mainmenuCHOICE == 2)
		{
			REGISTER(activeACCOUNTS);
		}

		int homeCHOICE;
		goBACK = 'H';

		while (goBACK == 'H' || goBACK == 'h')
		{
			cout << endl << "********** HOME PAGE ***********" << endl;

			cout << "[1].MY PROFILE" << endl <<
				"______________________" << endl
				<< "[2].MARKET PLACE" << endl <<
				"______________________" << endl
				<< "[3].SELL AN ITEM" << endl <<
				"______________________" << endl
				<< "[4].MONTHLY REPORT" << endl <<
				"______________________" << endl
				<< "[5].Write your feedback " << endl <<
				"______________________" << endl;

			cout << endl << "PLEASE, TYPE YOUR CHOICE IN THE FORM OF NUMBERS [1/2/3/4/5]" << endl <<
				"=================================================" << endl << endl;

			cin >> homeCHOICE;
			cout << "**********" << endl;

			if (homeCHOICE == 1)
			{
				cout << "Name: " << MYACCOUNT.NAME << endl
					<< "Email: " << MYACCOUNT.EMAIL << endl
					<< "Address: " << MYACCOUNT.deliveryADDRESS << endl
					<< "My Points:" << MYACCOUNT.POINTS << endl
					<< "Phone Number: " << MYACCOUNT.phoneNUMBER << endl
					<< "MY password: " << MYACCOUNT.PW << endl
					<< "=================================================" << endl;

				int profileCHOICE;
				char profile_validCHOICE = 'y';

				while (profile_validCHOICE == 'y' || profile_validCHOICE == 'Y')
				{
					cout << "[1]. My buying Requests" << endl
						<< "[2].Sold Items History" << endl
						<< "Click the number of your choice [1/2]" << endl;

					cin >> profileCHOICE;
					cout << "****************" << endl;

					myREQUESTS_AND_SOLD_ITEMS(profileCHOICE);

					cout << endl << "Back to my profile?[y/n]" << endl;
					cin >> profile_validCHOICE;
					cout << "*********" << endl;
				}

				cout << endl << "To go back to HOME PAGE, TYPE H" << endl
					<< "Logout/Exit ,Back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;
			}

			else if (homeCHOICE == 2)
			{
				char market_validCHOICE = 'y';       //used if user entered invalid entry

				for (i = 0; i < activeACCOUNTS; i++)
				{
					for (j = 0; j < 10; j++)
					{
						if (listofMEMBERS[i].listofITEMS[j].statues == "AVAILABLE")
						{
							cout << ". category: " << listofMEMBERS[i].listofITEMS[j].CATEGORY << endl
								<< "item:" << listofMEMBERS[i].listofITEMS[j].NAME << endl
								<< "item number: " << listofMEMBERS[i].listofITEMS[j].itemNUM << endl
								<< "Starting price is: " << listofMEMBERS[i].listofITEMS[j].STARTING_BID_PRICE << endl
								<< "Starting Auction Date: " << listofMEMBERS[i].listofITEMS[j].START_DATE.day << '/'
								<< listofMEMBERS[i].listofITEMS[j].START_DATE.month << '/'
								<< listofMEMBERS[i].listofITEMS[j].START_DATE.year << endl
								<< "Ending Auction Date: " << listofMEMBERS[i].listofITEMS[j].END_DATE.day
								<< '/' << listofMEMBERS[i].listofITEMS[j].END_DATE.month << '/'
								<< listofMEMBERS[i].listofITEMS[i].END_DATE.year << endl
								<< "Statues: " << listofMEMBERS[i].listofITEMS[j].statues << endl <<
								"______________________________" << endl << endl;
						}
					}
				}

				while (market_validCHOICE == 'y' || market_validCHOICE == 'Y')
				{
					cout << "1.SEARCH FOR ITEM" << endl <<
						"______________________" << endl
						<< "2.BUY AN ITEM" << endl <<
						"______________________" << endl
						<< "Click the number of your choice [1/2]" << endl
						<< "______________________" << endl;

					int marketCHOICE;                           //variables stores users choice in market place
					cin >> marketCHOICE;
					cout << "***************" << endl;

					if (marketCHOICE == 1)
					{
						char anotherSEARCH = 'y';

						do {

							string search_by, searchingCATEGORY;  int searchingPRICE = 0;

							SEARCH(search_by, searchingCATEGORY, searchingPRICE);


							cout << "Would you like to try searching again? [y/n]" << endl;
							cin >> anotherSEARCH; cout << "************" << endl;
						} while (anotherSEARCH == 'y' || anotherSEARCH == 'Y');

						market_validCHOICE = 'n';
					}

					else if (marketCHOICE == 2)
					{
						string required_item;   char buyerAPPROVAL = 'y';
						BUYING(required_item, buyerAPPROVAL);
						market_validCHOICE = 'n';
					}
					else
					{
						cout << "Invalid choice, Please type either 1 or 2" << endl;
						cout << "Do you want to try again?[y/n]" << endl;
						cin >> market_validCHOICE;
						cout << "***************" << endl;
					}
				}

				cout << endl << "To go back to HOME PAGE, TYPE H" << endl
					<< "To go back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;
			}

			else if (homeCHOICE == 3)
			{
				int nItems = 0;

				SELLING(nItems);

				cout << endl << "To go back to HOME PAGE, TYPE H" << endl
					<< "Logout/Exit ,Back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;

			}

			else if (homeCHOICE == 4)
			{
				char anotherMONTH = 'y';
				do
				{
					MONTHLY_REPORT();
					cout << "Do you want to check another month [y/n]" << endl;
					cin >> anotherMONTH;
					cout << "*************" << endl;

				} while (anotherMONTH == 'y' || anotherMONTH == 'Y');

				cout << endl << "To go back to HOME PAGE, TYPE H" << endl
					<< "Logout/Exit ,Back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;
			}

			else if (homeCHOICE == 5)
			{
				char anotherFEEDBACK = 'y';
				while (anotherFEEDBACK == 'Y' || anotherFEEDBACK == 'y')
				{
					string feedBACK, feedback_ID; int ratings = 0;

					FEEDBACK(feedBACK, feedback_ID, ratings);

					cout << "TRY AGAIN? [Y/N]" << endl;
					cin >> anotherFEEDBACK; cout << "**********" << endl;

				}

				cout << endl << "To go back to HOME PAGE, TYPE H" << endl
					<< "To go back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;
			}

			else
			{
				cout << "Invalid entry, Please type a number between 1 to 5!" << endl << endl;

				cout << "To go back to HOME PAGE, TYPE H" << endl
					<< "Logout/Exit ,Back to Main Menu, TYPE E" << endl;
				cin >> goBACK;
				cout << "*************" << endl;
			}

		}                                      //Homepage while loop
	}                                          //MainMenu while loop
	return 0;
}