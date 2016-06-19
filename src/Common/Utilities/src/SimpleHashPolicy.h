#pragma once

namespace BitFunnel
{
    namespace SimpleHashPolicy
    {
        //*********************************************************************
        //
        // The Threadsafe policy configures the SimpleHashTable template to
        // perform threadsafe find and update operations. Note that the
        // Threadsafe policy does not support hash table resizing. Also note
        // the Threadsafe policy is less performant than the SingleThreaded
        // policy.
        //
        //*********************************************************************
        class Threadsafe
        {
        public:
            // Constructs a Threadsafe policy. Since Threadsafe does not
            // hash table resizing, the allowResize parameter must be set to
            // false. A value of true will result in an exception throw from
            // the constructor.
            Threadsafe(bool allowResize);

            // Uses interlocked compare exchange to atomically update a key in
            // a hash table slot from an existing expected value to a new desired
            // value if the value of the existing key is not changed before the
            // update operation performs. Returns false if slot of the key is
            // already updated.
            bool UpdateKeyIfUnchanged(volatile unsigned __int64* keys,
                                      unsigned slot,
                                      unsigned __int64 expectedCurrentKey,
                                      unsigned __int64 desiredKey);

            // Returns true if this instance allows hash table resizing. Since
            // the Threadsafe policy does not allow hash table resizing, this
            // method will always return false.
            bool AllowsResize() const;

        private:
            bool m_allowsResize;
        };


        //*********************************************************************
        //
        // The SingleThreaded policy configures the SimpleHashTable template to
        // perform single threaded find and update operations. This policy does
        // support hash table resizing. Note that SingleThreaded is more
        // performant than ThreadSafe.
        //
        //*********************************************************************
        class SingleThreaded
        {
        public:
            // Constructs a SingleThreaded policy. The allowResize parameter
            // configures the hash table's resize policy.
            SingleThreaded(bool allowResize);

            // Non-atomic method to update a key from an existing value to a 
            // desired new value in a hash table slot. Returns true if the key 
            // was successfully written. Returns false if the slot doesn't have
            // the expected existing key.
            bool UpdateKeyIfUnchanged(volatile unsigned __int64* keys,
                                      unsigned slot,
                                      unsigned __int64 expectedCurrentKey,
                                      unsigned __int64 desiredKey);

            // Returns true if the hash table is configured to allow resizing.
            bool AllowsResize() const;

        private:
            bool m_allowsResize;
        };
    }
}
