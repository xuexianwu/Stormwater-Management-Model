//-----------------------------------------------------------------------------
//   toolkitAPI.c
//
//   Project: EPA SWMM5
//   Version: 5.1
//   Date:    08/30/2016
//   Author:  B. McDonnell (EmNet LLC)
//
//   Exportable Functions for Project Definition API.
//
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"                    // defined constants
#include "macros.h"                    // macros used throughout SWMM
#include "enums.h"                     // enumerated variables
#include "error.h"                     // error message codes
#include "datetime.h"                  // date/time functions
#include "objects.h"                   // definitions of SWMM's data objects
#include "funcs.h"                     // declaration of all global functions
#include "text.h"                      // listing of all text strings 
#define  EXTERN                        // defined as 'extern' in headers.h
#include "globals.h"                   // declaration of all global variables

#include "swmm5.h"                     // declaration of exportable functions
#include "toolkitAPI.h"
#include "hash.h"

int DLLEXPORT  swmm_countObjects(int type, int *count)
//
// Input: 	type = object type (Based on ObjectType enum)
//			count = pointer to integer
// Output: 	returns API Error
// Purpose: uses Object Count table to find number of elements of an object
{	
	int errorcode = 0;
	
	if(type >= MAX_OBJ_TYPES)
	{
		errorcode = 901;
		return errorcode;
	}
	*count = Nobjects[type];
	
	return errorcode;
}

int DLLEXPORT swmm_getObjectId(int type, int index, char *id)
//
// Input: 	type = object type (Based on ObjectType enum)
//			index = Index of desired ID
//			id = pointer to id pass by reference
// Output: 	returns API Error
// Purpose: Gets ID for any object
{
	//Provide Empty Character Array 
	strcpy(id,"");
	
	//Is *.inp file open?
	//if (!IsOpenFlag) return(ERR_NOT_OPEN);
	
	int errorcode = 0;
	if(type >= MAX_OBJ_TYPES)
	{
		errorcode = 901;
		return(errorcode);
	}
	
	if (index < 0 || index >= Nobjects[type]) return(902);
	switch (type)
	{
		case GAGE:
			strcpy(id,Gage[index].ID); break;
		case SUBCATCH:
			strcpy(id,Subcatch[index].ID); break;
		case NODE:
			strcpy(id,Node[index].ID); break;
		case LINK:
			strcpy(id,Link[index].ID); break;
		case POLLUT:
			strcpy(id,Pollut[index].ID); break;
		case LANDUSE:
			strcpy(id,Landuse[index].ID); break;
		case TIMEPATTERN:
			strcpy(id,Pattern[index].ID); break;
		//case CURVE:
			//strcpy(id,Curve[index].ID); break;
		//case TSERIES:
			//strcpy(id,Tseries[index].ID); break;
		//case CONTROL:
			//strcpy(id,Rules[index].ID); break;
		case TRANSECT:
			strcpy(id,Transect[index].ID); break;
		case AQUIFER:
			strcpy(id,Aquifer[index].ID); break;
		case UNITHYD:
			strcpy(id,UnitHyd[index].ID); break;
		case SNOWMELT:
			strcpy(id,Snowmelt[index].ID); break;
		//case SHAPE:
		//strcpy(id,Shape[index].ID); break;
		//case LID:
		//	strcpy(id,LidProcs[index].ID); break;
   }

   return(errorcode);
}

int DLLEXPORT swmm_getNodeType(int index, int *Ntype)
//
// Input: 	index = Index of desired ID
//			Ntype = Node type (Based on enum NodeType)
// Output: 	returns API Error
// Purpose: Gets Node Type
{
	if (index < 0 || index >= Nobjects[NODE]) return(902);
	*Ntype = Node[index].type;
	return(0);
}

int DLLEXPORT swmm_getLinkType(int index, int *Ltype)
//
// Input: 	index = Index of desired ID
//			Ltype = Link type (Based on enum NodeType)
// Output: 	returns API Error
// Purpose: Gets Link Type
{
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	*Ltype = Link[index].type;
	return(0);
}

int DLLEXPORT swmm_getLinkConnections(int index, int *Node1, int *Node2)
//
// Input: 	type = object type (Based on ObjectType enum)
//			index = Index of desired ID
// Output: 	Node1 and Node2
// Purpose: Gets link Connection ID Indeces
{
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	
	*Node1 = Link[index].node1;
	*Node2 = Link[index].node2;
	
	return(0);
}

int DLLEXPORT swmm_getNodeParam(int index, int Param, double *value)
//
// Input: 	index = Index of desired ID
//			param = Parameter desired (Perhaps define enum )
//			id = pointer to id pass by reference
// Output: 	returns API Error
// Purpose: Gets Node Parameter
{
	// Add Checks later on (08/31/2016 ** BEM)
	// Add Enum later for values
	if (index < 0 || index >= Nobjects[NODE]) return(902);
	
	switch(Param)
	{
		// invertElev
		case 0: *value = Node[index].invertElev; break;			
		// fullDepth
		case 1: *value = Node[index].fullDepth; break;		
		// surDepth
		case 2: *value = Node[index].surDepth; break;	
		// pondedArea
		case 3: *value = Node[index].pondedArea; break;	
		// initDepth
		case 4: *value = Node[index].initDepth; break;					
	}
	return(0);
}


int DLLEXPORT swmm_getLinkParam(int index, int Param, double *value)
//
// Input: 	index = Index of desired ID
//			param = Parameter desired (Perhaps define enum )			
//			id = pointer to id pass by reference
// Output: 	returns API Error
// Purpose: Gets Link Parameter
{
	// Add Checks later on (08/31/2016 ** BEM)
	// Add Enum later for values
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	
	switch(Param)
	{
		// offset1
		case 0: *value = Link[index].offset1; break;			
		// offset2
		case 1: *value = Link[index].offset2; break;		
		// q0
		case 2: *value = Link[index].q0; break;	
		// qLimit
		case 3: *value = Link[index].qLimit; break;	
		// cLossInlet
		case 4: *value = Link[index].cLossInlet; break;		
		// cLossOutlet
		case 5: *value = Link[index].cLossOutlet; break;		
		// cLossAvg
		case 6: *value = Link[index].cLossAvg; break;		
		// seepRate
		case 7: *value = Link[index].seepRate; break;
	}
	return(0);
}


int DLLEXPORT swmm_getLinkDirection(int index, signed char *value)
//
// Input: 	index = Index of desired ID
// Output: 	Link Direction (Only changes is slope < 0)
// Purpose: Gets Link Direction
{
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	*value = Link[index].direction;
	return(0);
}



int DLLEXPORT swmm_getSubcatchParam(int index, int Param, double *value)
//
// Input: 	index = Index of desired ID
//			param = Parameter desired (Perhaps define enum )
//			id = pointer to id pass by reference
// Output: 	returns API Error
// Purpose: Gets Subcatchment Parameter
{
	// Add Checks later on (08/31/2016 ** BEM)
	// Add Enum later for values
	if (index < 0 || index >= Nobjects[SUBCATCH]) return(902);
	
	switch(Param)
	{
		// width
		case 0: *value = Subcatch[index].width; break;			
		// area
		case 1: *value = Subcatch[index].area; break;		
		// fracImperv
		case 2: *value = Subcatch[index].fracImperv; break;	
		// slope
		case 3: *value = Subcatch[index].slope; break;	
		// curbLength
		case 4: *value = Subcatch[index].curbLength; break;		
		// initBuildup
		//case 5: *value = Subcatch[index].initBuildup; break;					
	}
	return(0);	
}

int DLLEXPORT swmm_getSubcatchOutConnection(int index, int *type, int *Index )
//
// Input: 	type = object type (Based on ObjectType enum) (Subcatchments can load to Node or another Subcatchment)
//			index = Index of desired ID
// Output: 	Node1 and Node2
// Purpose: Gets Subcatchment Connection ID Indeces for either Node or Subcatchment
{
	if (index < 0 || index >= Nobjects[SUBCATCH]) return(902);
	
	if (Subcatch[index].outNode == -1 && Subcatch[index].outSubcatch == -1)
	{
		*Index = index; // Case of self Loading subcatchment
		*type = SUBCATCH;
	}
	if (Subcatch[index].outNode >= 0)
	{
		*Index = Subcatch[index].outNode;
		*type = NODE;
	}
	if (Subcatch[index].outSubcatch >= 0)
	{
		*Index = Subcatch[index].outSubcatch;
		*type = SUBCATCH;
	}
	
	return(0);
}




//-------------------------------
// Active Simulation Results API
//-------------------------------

int DLLEXPORT swmm_getCurrentDateTimeStr(char *dtimestr)
{
	//Provide Empty Character Array 
	
    char     theDate[12];
    char     theTime[9];
	char     _DTimeStr[22];
	
	DateTime currentTime;
	// Fetch Current Time
	currentTime = getDateTime(NewRoutingTime);
	// Convert To Char
    datetime_dateToStr(currentTime, theDate);
    datetime_timeToStr(currentTime, theTime);
	
	strcpy(_DTimeStr, theDate);
	strcat(_DTimeStr, " ");
	strcat(_DTimeStr, theTime);
	
	strcpy(dtimestr, _DTimeStr);
	return(0);
}


int DLLEXPORT swmm_getNodeResult(int index, int type, double *result)
//
// Input: 	index = Index of desired ID	
//			type = Result Type
// Output: 	result = result data desired (byref)
// Return: 	
// Purpose: Gets Node Simulated Value
{
	if (index < 0 || index >= Nobjects[NODE]) return(902);
	
	switch (type)
	{
		// Total Inflow
		case 0: *result = Node[index].inflow; break; 
		// Total Outflow
		case 1: *result = Node[index].outflow; break; 
		// Losses (evap + exfiltration loss)
		case 2: *result = Node[index].losses; break; 
		// Current Volume
		case 3: *result = Node[index].newVolume; break; 
		// overflow
		case 4: *result = Node[index].overflow; break; 
		// Current water depth
		case 5: *result = Node[index].newDepth; break; 
		// Current water head
		case 6: *result = Node[index].newDepth + Node[index].invertElev; break; 		
		// Current Lateral Inflow
		case 7: *result = Node[index].newLatFlow; break; 
	}
	return(0);
}

int DLLEXPORT swmm_getLinkResult(int index, int type, double *result)
//
// Input: 	index = Index of desired ID	
//			type = Result Type
// Output: 	result = result data desired (byref)
// Return: 	
// Purpose: Gets Node Simulated Value
{
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	
	switch (type)
	{
		// Current Flow
		case 0: *result = Link[index].newFlow; break; 
		// Current Depth
		case 1: *result = Link[index].newDepth; break; 
		// Current Volume
		case 2: *result = Link[index].newVolume; break; 
		// Upstream Surface Area
		case 3: *result = Link[index].surfArea1; break; 
		// Downstream Surface Area
		case 4: *result = Link[index].surfArea2; break; 
		// Current Setting
		case 5: *result = Link[index].setting; break; 
		// Target Setting
		case 6: *result = Link[index].targetSetting; break; 	
		// Froude number
		case 7: *result = Link[index].froude; break; 			
	}
	return(0);
}

int DLLEXPORT swmm_getSubcatchResult(int index, int type, double *result)
//
// Input: 	index = Index of desired ID	
//			type = Result Type
// Output: 	result = result data desired (byref)
// Return: 	
// Purpose: Gets Node Simulated Value
{
	if (index < 0 || index >= Nobjects[SUBCATCH]) return(902);
	
	switch (type)
	{
		// Current Rainfall
		case 0: *result = Subcatch[index].rainfall; break; 
		// Current Evaporation Loss
		case 1: *result = Subcatch[index].evapLoss; break; 
		// Current Infiltration Loss
		case 2: *result = Subcatch[index].infilLoss; break; 
		// Subcatchment Runon
		case 3: *result = Subcatch[index].runon; break; 
		// Current Runoff
		case 4: *result = Subcatch[index].newRunoff; break; 
		// Current Snow Depth
		case 5: *result = Subcatch[index].newSnowDepth; break; 		
	}
	return(0);
}





//-------------------------------
// Setters API
//-------------------------------

int DLLEXPORT swmm_setLinkSetting(int index, double targetSetting)
//
// Input: 	index = Index of desired ID
//			value = New Target Setting		
// Output: 	returns API Error
// Purpose: Sets Link open fraction (Weir, Orifice, Pump, and Outlet)
{
	// Add Checks later on (11/03/2016 ** BEM)
	if (index < 0 || index >= Nobjects[LINK]) return(902);
	
	int l_type, errcode;
	
	// Get Link Type
	// errcode = swmm_getLinkType(index, &l_type);
	// WEIR, ORIFICES, PUMPS can have any value between [0,1]
	// CONDUIT can be only 0 or 1 * BEM 11/4/2016 investigate this...	
	
	Link[index].targetSetting  = targetSetting; 
	// Use internal function to apply the new setting
	link_setSetting(index, 0.0);
	
	// Add control action to RPT file if desired flagged
    if (RptFlags.controls)
	{
		DateTime currentTime;
		currentTime = getDateTime(NewRoutingTime);
		char _rule_[11] = "ToolkitAPI";
		report_writeControlAction(currentTime, Link[index].ID, targetSetting, _rule_);
	}
	return(0);
}











