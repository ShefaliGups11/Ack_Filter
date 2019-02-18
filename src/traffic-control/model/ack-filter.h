#include "ns3/object-factory.h"
#include <list>
#include <map>
#include "ns3/pointer.h"
#include "ns3/queue-disc.h"

namespace ns3 {

class Ipv4QueueDiscItem;
template <typename Item>
class Queue;

class AckFilter : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
//  static TypeId GetTypeId (void);
/**
 * \brief AckFilter constructor
 */
  AckFilter ();

  virtual ~AckFilter ();
  virtual void AckFilterMain (Ptr<QueueDisc> queue);

};

}
