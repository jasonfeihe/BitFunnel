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

#include <memory>                       // std::unqiue_ptr member.
#include <vector>                       // std::vector member.

#include "BitFunnel/Chunks/IChunkProcessor.h"   // Base class.
#include "BitFunnel/NonCopyable.h"      // Base class.
#include "Document.h"                   // std::unique_ptr<Document>.


namespace BitFunnel
{
    class IConfiguration;
    class IIngestor;


    class ChunkIngestorFactory : public IChunkProcessorFactory
    {
    public:
        ChunkIngestorFactory(IConfiguration const & configuration,
                             IIngestor& ingestor,
                             bool cacheDocuments);

        //
        // IChunkProcessorFactory methods
        //

        virtual std::unique_ptr<IChunkProcessor> Create() override;

    private:
        IConfiguration const & m_config;
        IIngestor& m_ingestor;
        bool m_cacheDocuments;
    };


    class ChunkIngestor : public NonCopyable, public IChunkProcessor
    {
    public:
        ChunkIngestor(IConfiguration const & configuration,
                      IIngestor& ingestor,
                      bool cacheDocuments);

        //
        // IChunkProcessor methods.
        //
        virtual void OnFileEnter() override;
        virtual void OnDocumentEnter(DocId id) override;
        virtual void OnStreamEnter(Term::StreamId id) override;
        virtual void OnTerm(char const * term) override;
        virtual void OnStreamExit() override;
        virtual void OnDocumentExit(size_t bytesRead) override;
        virtual void OnFileExit() override;

    private:
        //
        // Constructor parameters
        //
        IConfiguration const & m_config;
        IIngestor& m_ingestor;
        bool m_cacheDocuments;

        //
        // Other members
        //
        std::unique_ptr<Document> m_currentDocument;
    };
}
