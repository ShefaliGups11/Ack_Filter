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

int 
AckFilter::AckFilterSackCompare(Ptr<QueueDiscItem> item_a, Ptr<QueueDiscItem> item_b)
{
return 1;
}

bool
AckFilter::AckFilterMayDrop (Ptr<QueueDiscItem> item, uint32_t tstamp,uint32_t tsecr)
{
  uint8_t flags;
  if((((item->GetUint8Value (QueueItem::TCP_FLAGS,flags)) & uint32_t(0x0F3F0000)) != TcpHeader::ACK) || item->HasTcpOption(TcpOption::SACKPERMITTED) || item->HasTcpOption(TcpOption::WINSCALE) || item->HasTcpOption(TcpOption::UNKNOWN))
     { 
     return false;
     }
  else if(item->HasTcpOption(TcpOption::TS))
  {
  uint32_t tstamp_check,tsecr_check;
  item->TcpGetTimestamp (tstamp_check,tsecr_check);
  if((tstamp_check < tstamp) || (tsecr_check < tsecr))
     return false;
     else
     return true;
  }
  else
      return true;
}

void
AckFilter::AckFilterMain (Ptr<QueueDisc> Qu)
{
  Ptr<Queue<QueueDiscItem> > queue =  Qu->GetInternalQueue (0);
  bool hastimestamp;
  uint32_t tstamp, tsecr;
  Ipv4Address src1,src2,dst1,dst2;

  // No other possible ACKs to filter
  if (*(queue->Tail ()) == *(queue->Head ()))
    {
      return;
    }
  Ptr<QueueDiscItem> tail = *(queue->Tail ());
  if (tail->GetL4Protocol () != 6)
    {
      return;
    }

  hastimestamp = tail->TcpGetTimestamp (tstamp,tsecr);
  std::cout<<hastimestamp;
  //the 'triggering' packet need only have the ACK flag set.
  //also check that SYN is not set, as there won't be any previous ACKs.
  uint8_t flags;
  tail->GetUint8Value (QueueItem::TCP_FLAGS,flags);
  if ((flags & (TcpHeader::SYN | TcpHeader::ACK)) != TcpHeader::ACK)
    {
      return;
    }
  auto prev = queue->Head ();

  //Triggered ack is at tail of the queue we have already returned if it is the only
  //packet in the flow. Loop through the rest of the queue looking for pure ack
  //with the same 5-tuple as the triggered one
  for (auto check = queue->Head (); check != queue->Tail (); prev = check,check++)
    {
      if ((*check)->GetL4Protocol () != 6 || ((*check)->TcpSourcePort () != tail->TcpSourcePort()) || ((*check)->TcpDestinationPort () != tail->TcpDestinationPort()))
        {
          continue;
          (*check)->GetSourceL3address(src1);
           tail->GetSourceL3address (src2);
           (*check)->GetDestL3address(dst1);
            tail->GetDestL3address (dst2);

        }
      Ptr<QueueDiscItem> item = *check;
      SequenceNumber32 abc = (*check)->GetxyzHeader();
      std::cout <<abc;

    }
}

}


