// The MIT License (MIT)

// Copyright (c) 2016, Microsoft

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <vector>   // std::vector parameter.
#include <string>   // Template parameter.

#include "BitFunnel/Chunks/IChunkManifestIngestor.h" // Base class.


namespace BitFunnel
{
    class IChunkProcessorFactory;

    class BuiltinChunkManifest : public IChunkManifestIngestor
    {
    public:
        typedef std::vector<std::pair<size_t, char const *>> ChunkArray;

        BuiltinChunkManifest(ChunkArray const & chunks,
                             IConfiguration const & config,
                             IIngestor& ingestor,
                             bool cacheDocuments);

        //
        // IChunkManifestIngestor
        //

        virtual size_t GetChunkCount() const override;

        virtual void IngestChunk(size_t index) const override;

    private:

        //
        // Constructor parameters
        //
        ChunkArray const & m_chunks;
        IConfiguration const & m_configuration;
        IIngestor& m_ingestor;
        bool m_cacheDocuments;
    };
}
