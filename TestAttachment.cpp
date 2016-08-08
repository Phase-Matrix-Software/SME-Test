#include "TestAttachment.h"
#include <iostream>

TestAttachment::TestAttachment(SME::Level::Entity::Entity* entity)
:SME::Level::Entity::Attachment::Attachment(entity){ }

void TestAttachment::onPosChanged(glm::vec3 pos){}
void TestAttachment::onVelChanged(glm::vec3 vel){}
void TestAttachment::onRotChanged(glm::vec3 rot){}
void TestAttachment::onUpdate(){}

TestAttachment::~TestAttachment(){}