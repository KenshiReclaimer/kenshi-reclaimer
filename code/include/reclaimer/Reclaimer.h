#pragma once

#include <ogre/Ogre.h>
#include <ogre/OgrePlugin.h>

class ReclaimerVM;

class ReclaimerMain : public Ogre::Plugin
{
public:
    virtual const Ogre::String& getName() const { return "Reclaimer"; };

    virtual void install() override;
    virtual void initialise() override;
    virtual void shutdown() override;
    virtual void uninstall() override;

private:
    ReclaimerVM* m_vm;
};