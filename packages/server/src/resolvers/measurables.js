const _ = require('lodash');

const data = require('../data');
const { Pagination } = require('../pagination');

/**
 * @param {*} root
 * @param {object} args
 * @param {Models.ObjectID} args.creatorId
 * @param {Models.ObjectID} args.seriesId
 * @param {Models.ObjectID} args.channelId
 * @param {Models.ObjectID} args.measuredByAgentId
 * @param {string} args.resultOrLatestMeasurementForAgentId
 * @param {string[]} args.states
 * @param {string[]} args.isArchived
 * @param {string} args.after
 * @param {string} args.before
 * @param {number} args.last
 * @param {number} args.first
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<Models.Measurable[]>}
 */
async function all(root, args, context, info) {
  const filter = {
    creatorId: _.get(args, 'creatorId'),
    seriesId: _.get(args, 'seriesId'),
    channelId: _.get(args, 'channelId'),
    states: _.get(args, 'states'),
    isArchived: _.get(args, 'isArchived'),
  };
  const pagination = new Pagination(args);
  const options = {
    isAdmin: _.get(context, 'agent.isAdmin'),
    agentId: _.get(context, 'agent.id'),
    measuredByAgentId: _.get(args, 'measuredByAgentId'),
  };
  // tricky
  context.resultOrLatestMeasurementForAgentId = args.resultOrLatestMeasurementForAgentId;
  const result = await data.measurables.getAll(filter, pagination, options);
  return result.data;
}

/**
 * @param {*} root
 * @param {object} args
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function one(root, args, context, info) {
  const agentId = _.get(context, 'agent.id');
  return await data.measurables.getOne(args.id, { agentId });
}

/**
 * @param {*} root
 * @param {object} args
 * @param {object} args.input
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function create(root, args, context, info) {
  const creator = context.creator;
  const agentId = _.get(context, 'agent.id');
  const datas = {
    ...args.input,
    creatorId: agentId,
  };
  return await data.measurables.createOne(datas, creator);
}

/**
 * @param {*} root
 * @param {object} args
 * @param {Models.ObjectID} args.id
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function archive(root, args, context, info) {
  const { id } = args;
  return await data.measurables.archive(id);
}

/**
 * @param {*} root
 * @param {object} args
 * @param {Models.ObjectID} args.id
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function unarchive(root, args, context, info) {
  const { id } = args;
  return await data.measurables.unArchive(id);
}

/**
 * @param {*} root
 * @param {object} args
 * @param {Models.ObjectID} args.id
 * @param {object} args.input
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function update(root, args, context, info) {
  const id = args.id;
  const datas = args.input;
  const creator = context.creator;
  return await data.measurables.updateOne(id, datas, creator);
}

/**
 * @param {*} root
 * @param {Models.ObjectID} root.id
 * @param {object} args
 * @param {Schema.Context} context
 * @param {object} info
 * @returns {Promise<*|Array<Model>>}
 */
async function openedCount(root, args, context, info) {
  const channelId = root.id;
  return await data.measurables.getOpenedCount(channelId);
}

module.exports = {
  one,
  all,
  update,
  unarchive,
  archive,
  create,
  openedCount,
};
