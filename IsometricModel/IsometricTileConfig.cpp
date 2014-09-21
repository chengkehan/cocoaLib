//
//  IsometricTileConfig.cpp
//  IsometricModel
//
//  Created by jimCheng on 14-8-28.
//  Copyright (c) 2014年 JimCheng. All rights reserved.
//

#include "IsometricTileConfig.h"
#include "IsometricPairValue.h"
#include "IsometricPairValueGroup.h"
#include "IsometricPairValue.h"
#include "tinyxml2.h"

using namespace jcgame;
using namespace tinyxml2;

/* PUBLIC */

IsometricTileConfig::IsometricTileConfig():
    numFrames(0), frames(nullptr)
{
    memset(&metadata, 0, sizeof(IsometricTileConfig_Metadata));
}

IsometricTileConfig::~IsometricTileConfig()
{
    releaseFrames();
}

bool IsometricTileConfig::init(const char *xmlString)
{
    if (frames != nullptr)
    {
        return false;
    }
    if (xmlString == nullptr)
    {
        return false;
    }
    
    XMLDocument doc;
    doc.Parse(xmlString);
    if (doc.ErrorID() != XML_NO_ERROR)
    {
        return false;
    }
    
    // Metadata
    {
        XMLElement* metaXMLElement = doc.FirstChildElement("plist")->FirstChildElement("dict")->FirstChildElement("dict")->NextSiblingElement()->NextSiblingElement();
        XMLElement* childXMLElement = nullptr;
        for (childXMLElement = metaXMLElement->FirstChildElement(); childXMLElement != nullptr; childXMLElement = childXMLElement->NextSiblingElement()->NextSiblingElement())
        {
            const char* key = childXMLElement->GetText();
            if (strcmp(key, "size") == 0)
            {
                IsometricPairValue pairValue;
                if(pairValue.set(childXMLElement->NextSiblingElement()->GetText()))
                {
                    metadata.size.width = pairValue.getValue0();
                    metadata.size.height = pairValue.getValue1();
                }
                else
                {
                    return false;
                }
            }
        }
    }
    
    // Frames
    {
        XMLElement* framesXMLElement = doc.FirstChildElement("plist")->FirstChildElement("dict")->FirstChildElement("dict");
        
        // Count num frames
        int numFrames = 0;
        XMLElement* childXMLElement = nullptr;
        for (childXMLElement = framesXMLElement->FirstChildElement(); childXMLElement != nullptr; childXMLElement = childXMLElement->NextSiblingElement())
        {
            ++numFrames;
        }
        // key-dict,key-dict,key-dict pair match
        if (numFrames % 2 != 0)
        {
            return false;
        }
        if (numFrames == 0)
        {
            return false;
        }
        // alloc
        this->numFrames = (int)(numFrames * 0.5f);
        frames = (IsometricTileConfig_Frame*)malloc(sizeof(IsometricTileConfig_Frame) * numFrames);
        // memory low
        if (frames == nullptr)
        {
            return false;
        }
        // init data
        int index = 0;
        IsometricPairValueGroup pairValueGroup;
        IsometricPairValue pairValue;
        for (childXMLElement = framesXMLElement->FirstChildElement(); childXMLElement != nullptr; childXMLElement = childXMLElement->NextSiblingElement(), ++index)
        {
            // dict node
            childXMLElement = childXMLElement->NextSiblingElement();
            for (XMLElement* keyXMLElement = childXMLElement->FirstChildElement(); keyXMLElement != nullptr; keyXMLElement = keyXMLElement->NextSiblingElement()->NextSiblingElement())
            {
                const char* key = keyXMLElement->GetText();
                XMLElement* valueXMLElement = keyXMLElement->NextSiblingElement();
                IsometricTileConfig_Frame* frame = &frames[index];
                if (strcmp(key, "frame") == 0)
                {
                    if(pairValueGroup.set(valueXMLElement->GetText()))
                    {
                        if (pairValueGroup.getNumValues() == 2)
                        {
                            frame->frame.point.x = pairValueGroup.getValue(0)->getValue0();
                            frame->frame.point.y = pairValueGroup.getValue(0)->getValue1();
                            frame->frame.size.width = pairValueGroup.getValue(1)->getValue0();
                            frame->frame.size.height = pairValueGroup.getValue(1)->getValue1();
                        }
                        else
                        {
                            releaseFrames();
                            return false;
                        }
                    }
                    else
                    {
                        releaseFrames();
                        return false;
                    }
                }
                else if (strcmp(key, "offset") == 0)
                {
                    if(pairValue.set(valueXMLElement->GetText()))
                    {
                        frame->offset.x = pairValue.getValue0();
                        frame->offset.y = pairValue.getValue1();
                    }
                    else
                    {
                        releaseFrames();
                        return false;
                    }
                }
                else if (strcmp(key, "sourceColorRect") == 0)
                {
                    if(pairValueGroup.set(valueXMLElement->GetText()))
                    {
                        frame->sourceColorRect.point.x = pairValueGroup.getValue(0)->getValue0();
                        frame->sourceColorRect.point.y = pairValueGroup.getValue(0)->getValue1();
                        frame->sourceColorRect.size.width = pairValueGroup.getValue(1)->getValue0();
                        frame->sourceColorRect.size.height = pairValueGroup.getValue(1)->getValue1();
                    }
                    else
                    {
                        releaseFrames();
                        return false;
                    }
                }
                else if (strcmp(key, "sourceSize") == 0)
                {
                    if(pairValue.set(valueXMLElement->GetText()))
                    {
                        frame->sourceSize.width= pairValue.getValue0();
                        frame->sourceSize.height = pairValue.getValue1();
                    }
                    else
                    {
                        releaseFrames();
                        return false;
                    }
                }
                else
                {
                    // Do nothing
                }
            }
        }
    }
    
    // Print xml content for debug
//    XMLPrinter printer;
//    metaXMLElement->Accept(&printer);
//    printf("%s", printer.CStr());
    
    return true;
}

const IsometricTileConfig_Metadata* IsometricTileConfig::getMetadata() const
{
    return &metadata;
}

int IsometricTileConfig::getNumFrames() const
{
    return numFrames;
}

const IsometricTileConfig_Frame* IsometricTileConfig::getFrame(int index) const
{
    if (index < 0 || index >= numFrames)
    {
        return nullptr;
    }
    
    return &frames[index];
}

/* PRIVATE */

void IsometricTileConfig::releaseFrames()
{
    if (frames != nullptr)
    {
        delete frames;
        frames = nullptr;
        numFrames = 0;
    }
}



