#include "RSIXml.h"


int RSIXmlLoader::parseXml(std::vector<IValue> &addrspace, 
			 std::unordered_map<std::string, int> &dataIndexMap,
			 std::unordered_map<std::string, EntityBase*> &fbMap)
{
	TiXmlElement* rootEle = doc.RootElement(); 

	TiXmlElement* decEle;
	if(getNodeByName(rootEle, "DECLARE", decEle)) {

		TiXmlElement* varEle ;
		if(getNodeByName(decEle, "VARIABLES", varEle)) {
			// std::cout << varEle->Value() << std::endl;

			TiXmlElement* vEle = varEle->FirstChildElement();
			for(; vEle != NULL; vEle = vEle->NextSiblingElement()) {
				std::string varName;
				std::string varVal("0");

				TiXmlAttribute* attr = vEle->FirstAttribute();
				for(; attr != NULL; attr = attr->Next()) {

					std::string attrName = attr->Name();
					if(attrName == "NAME") {
						varName = attr->Value();
					} else if(attrName == "INIT"){
						varVal = attr->Value();
					}

				}

				IValue val = std::stod(varVal);
				int curIndex = addrspace.size();

				dataIndexMap.insert(std::pair<std::string, int>(varName, curIndex));
				addrspace.push_back(val);
			}

		}
		
		TiXmlElement* fbNode ;
		if(getNodeByName(decEle, "FUNBLOCK", fbNode)) {

			TiXmlElement* fbEle = fbNode->FirstChildElement();
			for(; fbEle != NULL; fbEle = fbEle->NextSiblingElement()) {

				/* get fb entity name */
				TiXmlAttribute* attr = fbEle->FirstAttribute(); // NAME property in xml file for fb
				std::string fbName = attr->Value();

				/* get fb entity pointer */
				attr = attr->Next();     		// TYPE property in xml file for fb
				EntityBase* entity = EntityFactory::getEntity(attr->Value());

				/* config fb entity */
				for(attr = attr->Next(); attr != NULL; attr = attr->Next()) {
					entity->setConfig(attr->Name(), attr->Value());
				}

				fbMap.insert(std::pair<std::string, EntityBase*>(fbName, entity));
			}

		}

	}


	TiXmlElement* commEle;
	if(getNodeByName(rootEle, "COMMUNICATION", commEle)) {
		EntityBase* entity = EntityFactory::getEntity("COMMUNICATION");

		TiXmlElement* configEle ;
		if(getNodeByName(commEle, "CONFIG", configEle)) {
			TiXmlElement* cEle = configEle->FirstChildElement();
			for(; cEle != NULL; cEle = cEle->NextSiblingElement()) {
				entity->setConfig(cEle->Value(), cEle->GetText());
			}
		}

		fbMap.insert(std::pair<std::string, EntityBase*>("COMMUNICATION", entity));
	}
}


bool RSIXmlLoader::getXmlDeclare(std::string &strVersion,  
                   				 std::string &strStandalone,  
                   				 std::string &strEncoding)  
{  
    
	TiXmlNode* pXmlFirst = doc.FirstChild();     
	if (NULL != pXmlFirst) {    
		TiXmlDeclaration* pXmlDec = pXmlFirst->ToDeclaration();    
		if (NULL != pXmlDec) {    
			strVersion = pXmlDec->Version();  
			strStandalone = pXmlDec->Standalone();  
			strEncoding = pXmlDec->Encoding();  
		}  
	}  
	return true;  
}  


bool RSIXmlLoader::getNodeByName(TiXmlElement* pRootEle,std::string strNodeName,TiXmlElement* &Node)  
{  
	if (strNodeName == pRootEle->Value()) {  
		Node = pRootEle;  
		return true;  
	}  
	TiXmlElement* pEle = pRootEle;    
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {    
		if(getNodeByName(pEle, strNodeName, Node)) {
			return true;  
		}
	}    
	return false;  
}    