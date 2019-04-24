const _ = require('lodash');
const { rule } = require('graphql-shield');

/**
 * @param {*} root
 * @param {object} args
 * @param {Schema.Context} context
 * @param {object} info
 * @return {Promise<boolean>}
 */
async function isAuthenticatedRule(root, args, context, info) {
  const agentId = _.get(context, 'agent.id');
  const result = !!agentId;
  console.log(`\x1b[33m Rule Agents (isAuthenticatedRule) ` +
    `agentId "${agentId}", result = "${result}"\x1b[0m`);
  return result;
}

/** @type {Rule} */
const isAuthenticated = rule({
  cache: 'no_cache',
})(isAuthenticatedRule);

module.exports = {
  isAuthenticated,
  isAuthenticatedRule,
};
