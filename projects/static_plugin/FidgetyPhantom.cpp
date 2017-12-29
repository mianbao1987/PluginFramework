#include "FidgetyPhantom.h"
#include <string.h>
#include <utils/utils.h>

void * FidgetyPhantom::create(PF_ObjectParams * para)
{
  return new FidgetyPhantom(para);
}

apr_int32_t FidgetyPhantom::destroy(void * p)
{
  if (!p)
    return -1;
  delete (FidgetyPhantom *)p;
  return 0;
}

FidgetyPhantom::FidgetyPhantom(PF_ObjectParams * para)
{
	m_params.objectType = para->objectType;
	m_params.platformServices = para->platformServices;
}

FidgetyPhantom::~FidgetyPhantom()
{
}

void FidgetyPhantom::getInitialInfo(ActorInfo * info)
{
  ::strcpy((char *)info->name, "FidgetyPhantom");
  info->attack = 15;
  info->damage = 2;
  info->defense = 6;
  info->health = 7;
  info->movement = 3;

  // Irrelevant. Will be assigned by system later
  info->id = 0;
  info->location_x = 0;
  info->location_y = 0;
  log("Create FidgetyPhantom finish");
}

void FidgetyPhantom::play( ITurn * turnInfo)
{
  // Get self
  const ActorInfo * self = turnInfo->getSelfInfo();

  // Get first foe
  IActorInfoIterator * foes = turnInfo->getFoes();
  ActorInfo * foe  = foes->next();
  
  // Move towards and attack the first foe (usually the hero)
  Position p1(self->location_x, self->location_y);
  Position p2(foe->location_x, foe->location_y);

  Position closest = findClosest(p1, p2, self->movement);
  turnInfo->move(closest.first, closest.second);
  if (closest == p2)
    turnInfo->attack(foe->id);
}

void FidgetyPhantom::log(std::string log)
{
	const apr_byte_t * p_log = (const apr_byte_t*)(log.c_str());
	m_params.platformServices->invokeService(p_log, NULL);
}




