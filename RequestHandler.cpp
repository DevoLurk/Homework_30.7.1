#include "RequestHandler.h"

RequestHandler::RequestHandler() 
{
   m_tpool.start();
}
RequestHandler::~RequestHandler() 
{
   m_tpool.stop();
}