const { setContextChannel } = require('./channels');
const data = require('../data');

describe('Channels Middleware', () => {

  describe('setContextChannel() sets channel model into context', () => {
    const channelObj = {};
    beforeEach(() => {
      jest.spyOn(data.channels, 'getOne').mockReturnValue(
        Promise.resolve(channelObj),
      );
    });

    it('when arguments are passed', () => {
      const root = {};
      const args = { channelId: 'channelId1' };
      const context = {};
      const info = {};
      return setContextChannel(root, args, context, info).then((result) => {
        expect(data.channels.getOne).toHaveBeenCalledWith('channelId1');
        expect(result).toBe(undefined);
        expect(context.channel).toBe(channelObj);
      });
    });

    it('when root is passed', () => {
      const root = { channelId: 'channelId1' };
      const args = {};
      const context = {};
      const info = {};
      return setContextChannel(root, args, context, info).then((result) => {
        expect(data.channels.getOne).toHaveBeenCalledWith('channelId1');
        expect(result).toBe(undefined);
        expect(context.channel).toBe(channelObj);
      });
    });

    it('when context is passed', () => {
      const root = {};
      const args = {};
      const context = { channelId: 'channelId1' };
      const info = {};
      return setContextChannel(root, args, context, info).then((result) => {
        expect(data.channels.getOne).toHaveBeenCalledWith('channelId1');
        expect(result).toBe(undefined);
        expect(context.channel).toBe(channelObj);
      });
    });

  });

});

