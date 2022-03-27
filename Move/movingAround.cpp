void MappedSamplerVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
    if (auto* playingSound = dynamic_cast<OneSample*>(getCurrentlyPlayingSound().get())) {

        auto& data = *playingSound -> getAudioData();
        const float* const inL = data.getReadPointer(0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;
        
        int key = getInstrument();

        std::vector<int> hasPlaybackChannel;
        std::vector<float*> out;
        
        for (auto c : playToChannel) {
            if (busAvailable[c]) {
                hasPlaybackChannel.push_back(busChannelVector[c] - 1);
            }
        }
        
        DBG("Thread Voice------------------------------------");
        DBG("busAvailable");
        juce::String baS = "";
        for (auto ba : busAvailable) {
            baS = baS + (std::to_string(ba) + "  ");
        }
        DBG(baS);
        
        DBG("busChannelVec");
        juce::String bcV = "";
        for (auto bc : busChannelVector) {
            bcV = bcV + (std::to_string(bc) + "  ");
        }
        DBG(bcV);
        
        if (!hasPlaybackChannel.empty()) {
            for (auto c : hasPlaybackChannel) {
                out.push_back(outputBuffer.getWritePointer(c, startSample));
            }
            
            while (--numSamples >= 0) {
                auto pos = (int) sourceSamplePosition;
                auto alpha = (float)(sourceSamplePosition - pos);
                auto invAlpha = 1.0f - alpha;
                
                float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
                float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                    : l;
                
                l = EE.applyTo(l);
                r = EE.applyTo(r);
                
                for (auto o : out) {
                    *o++ += l;
                }
                
                sourceSamplePosition += pitchRatio;
                
                if (sourceSamplePosition > playingSound -> length || EE.getState() == 0) {
                    clearCurrentNote();
                    break;
                }
            }
        }
        else {
            stopNote(0, true);
        }
    }
}