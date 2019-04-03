#include "ns3/log.h"
#include "ack-filter.h"
#include "ns3/object-factory.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/header.h"
#include "ns3/ipv4-header.h"
#include "ns3/tcp-header.h"

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
  Ptr<Queue<QueueDiscItem> > queue =  Qu->GetInternalQueue (0);

  // No other possible ACKs to filter
  if (*(queue->Tail ()) == *(queue->Head ()))
    {
      return;
    }
  Ptr<QueueDiscItem> tail = *(queue->Tail ());
  if (tail->GetProtocol () != 6)
    {
      return;
    }

  //the 'triggering' packet need only have the ACK flag set.
  //also check that SYN is not set, as there won't be any previous ACKs.
  uint8_t flags;
  tail->GetUint8Value (QueueItem::TCP_FLAGS,flags);
  if ((flags & (TcpHeader::SYN | TcpHeader::ACK)) != TcpHeader::ACK)
    {
      return;
    }
  auto prev = queue->Head ();
  for (auto check = queue->Head (); check != queue->Tail (); prev = check,check++)
    {
      if ((*check)->GetProtocol () != 6)
        {
          continue;
        }
      Ptr<QueueDiscItem> item = *check;
      SequenceNumber32 abc = (*check)->GetxyzHeader();
      std::cout <<abc;

    }
}

}


