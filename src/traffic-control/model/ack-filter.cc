
#include "ns3/log.h"
#include "ack-filter.h"
#include "ns3/object-factory.h"
#include "ns3/drop-tail-queue.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AckFilter");

NS_OBJECT_ENSURE_REGISTERED (AckFilter);

TypeId AckFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AckFilter")
    .SetParent<Object> ()
    .SetGroupName ("TrafficControl")
    .AddConstructor<AckFilter> ();
    return tid;
}


AckFilter::AckFilter ()
{

}

AckFilter::~AckFilter ()
{

}

void
AckFilter::AckFilterMain (Ptr<QueueDisc> Qu)
{
 Ptr<Queue<QueueDiscItem>> abc = Qu->GetInternalQueue (0);
 Qu->GetCurrentSize ();
 
 /*for (uint16_t i=0 ;i< Qu->GetCurrentSize ();i++)
 {
 abc.Get (i);
 }*/
 
 
}

}


